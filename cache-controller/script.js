"use strict";

const memoryTable = document.querySelector("#memory-table");
const memoryToggle = document.querySelector("#toggle-memory");
const memoryPanel = document.querySelector("#memory-panel");
const layout = document.querySelector(".layout");
const historyList = document.querySelector("#step-history");
const memoryBlocks = new Map();
const writtenBackWords = new Set();
const caches = [Array(4).fill(null), Array(4).fill(null)];
const FSM_STEP_DELAY = 700;
let requestInProgress = false;
const cacheTables = [
  document.querySelector("#cache1-table tbody"),
  document.querySelector("#cache2-table tbody"),
];

function compactBits(text) {
  return text.replace(/\s+/g, "");
}

for (const row of memoryTable.tBodies[0].rows) {
  const tag = compactBits(row.cells[0].querySelector(".tag").textContent);
  const index = compactBits(row.cells[0].querySelector(".block-index").textContent);
  const key = `${tag}:${index}`;
  const words = Array.from(row.cells).slice(1).map((cell) => Number(cell.textContent));
  memoryBlocks.set(key, { key, tag, index, words });

  for (const form of document.querySelectorAll(".request-form")) {
    const option = document.createElement("option");
    option.value = key;
    option.textContent = `${tag} ${index}`;
    form.elements.block.add(option);
  }
}

function cacheIndex(block) {
  return Number.parseInt(block.index, 2) % 4;
}

function lineFor(cache, block) {
  const line = cache[cacheIndex(block)];
  return line && line.key === block.key ? line : null;
}

function writeBack(line) {
  if (line && line.state === "M") {
    memoryBlocks.get(line.key).words = [...line.words];
    line.words.forEach((_, word) => {
      writtenBackWords.add(`${line.key}:${word}`);
    });
  }
}

function renderCaches() {
  for (let cpu = 0; cpu < caches.length; cpu += 1) {
    cacheTables[cpu].replaceChildren();
    for (let index = 0; index < 4; index += 1) {
      const line = caches[cpu][index];
      const row = document.createElement("tr");
      const indexCell = document.createElement("td");
      indexCell.innerHTML = `<span class="block-index">00 0000 ${index.toString(2).padStart(4, "0")}</span>`;
      row.append(indexCell);

      let text_tag = "";

      if (line) {
        for (let i=0; i < line.tag.length; i+=4) {
          text_tag += line.tag.substr(i,4) + " ";
        }
  
        text_tag = text_tag.substr(0, text_tag.length-1);
      }


      const values = line
        ? ["1", line.state === "M" ? "1" : "0", '<span class="tag">' + text_tag + '</span>',
           ...line.words, line.state]
        : ["0", "0", "—", "—", "—", "—", "—", "I"];

      for (const value of values) {
        const cell = document.createElement("td");
        cell.innerHTML = String(value);
        row.append(cell);
      }

      row.lastElementChild.classList.add(`state-${line ? line.state : "I"}`);
      cacheTables[cpu].append(row);
    }
  }

  for (let index = 0; index < memoryTable.tBodies[0].rows.length; index += 1) {
    const row = memoryTable.tBodies[0].rows[index];
    const block = Array.from(memoryBlocks.values())[index];
    block.words.forEach((value, word) => {
      const cell = row.cells[word + 1];
      cell.textContent = String(value);
      cell.classList.toggle("written-back", writtenBackWords.has(`${block.key}:${word}`));
    });
  }
}

function showStep(message) {
  const item = document.createElement("li");
  item.textContent = message;
  historyList.prepend(item);
  while (historyList.children.length > 12) {
    historyList.lastElementChild.remove();
  }
}

function setFsmState(cpu, state) {
  const diagram = document.querySelector(`#cache${cpu + 1}-table`)
    .closest(".cache-panel")
    .querySelector(".fsm-diagram");
  const currentLabel = document.querySelector(`#cache${cpu + 1}-fsm-current`);

  for (const node of diagram.querySelectorAll(".fsm-state")) {
    const active = node.dataset.state === state;
    node.classList.toggle("is-active", active);
    if (active) {
      node.setAttribute("aria-current", "step");
    } else {
      node.removeAttribute("aria-current");
    }
  }

  currentLabel.textContent = `Estado actual: ${state}`;
}

function pauseForFsmStep() {
  return new Promise((resolve) => window.setTimeout(resolve, FSM_STEP_DELAY));
}

async function showFsmState(cpu, state) {
  setFsmState(cpu, state);
  await pauseForFsmStep();
}

function setFormsDisabled(disabled) {
  for (const form of document.querySelectorAll(".request-form")) {
    for (const control of form.elements) {
      control.disabled = disabled;
    }
    form.querySelector('button[type="submit"]').textContent = disabled
      ? "Procesando…"
      : "Ejecutar paso";
  }
}

function commitRead(line, word) {
  return `valor ${line.words[word]} (estado ${line.state})`;
}

async function executeRequest(cpu, block, word, operation, value) {
  const ownCache = caches[cpu];
  const otherCache = caches[1 - cpu];
  const index = cacheIndex(block);
  const line = lineFor(ownCache, block);
  const hit = Boolean(line);
  const victim = hit ? null : ownCache[index];
  const peerLine = lineFor(otherCache, block);

  if (peerLine) {
    setFsmState(1 - cpu, "Compare Tag");
  }
  await showFsmState(cpu, "Compare Tag");

  if (hit) {
    if (operation === "read") {
      const readResult = commitRead(line, word);
      return `CPU ${cpu + 1}: lectura hit en ${formatAddress(block, word)} → ${readResult}.`;
    }

    if (peerLine) {
      otherCache[index] = null;
    }
    line.words[word] = value;
    line.state = "M";
    return `CPU ${cpu + 1}: escritura hit en ${formatAddress(block, word)}; valor ${value}, estado M${peerLine ? " e invalidación de la otra caché" : ""}.`;
  }

  if (victim && victim.state === "M") {
    setFsmState(cpu, "Write Back");
    writeBack(victim);
    ownCache[index] = null;
    renderCaches();
    await pauseForFsmStep();
  }

  if (peerLine && peerLine.state === "M") {
    setFsmState(1 - cpu, "Write Back");
    writeBack(peerLine);
    if (operation === "read") {
      peerLine.state = "S";
    } else {
      otherCache[index] = null;
    }
    renderCaches();
    await pauseForFsmStep();
  }

  setFsmState(cpu, "Allocate");
  let words = peerLine ? [...peerLine.words] : [...block.words];
  if (peerLine) {
    if (operation === "read") {
      peerLine.state = "S";
    } else {
      otherCache[index] = null;
    }
  }

  const allocatedLine = {
    key: block.key,
    tag: block.tag,
    words,
    state: operation === "read" ? "S" : "M",
  };
  if (operation === "write") {
    allocatedLine.words[word] = value;
  }
  ownCache[index] = allocatedLine;
  renderCaches();
  await pauseForFsmStep();

  if (operation === "read") {
    return `CPU ${cpu + 1}: lectura miss en ${formatAddress(block, word)} → ${commitRead(allocatedLine, word)}.`;
  }
  return `CPU ${cpu + 1}: escritura miss en ${formatAddress(block, word)}; valor ${value}, estado M${peerLine ? " e invalidación de la otra caché" : ""}.`;
}

function formatAddress(block, word) {
  return `${block.tag} ${block.index} ${word.toString(2).padStart(2, "0")} 00`;
}

for (const form of document.querySelectorAll(".request-form")) {
  const operationSelect = form.elements.operation;
  const valueField = form.querySelector(".write-value");

  operationSelect.addEventListener("change", () => {
    valueField.hidden = operationSelect.value !== "write";
  });

  form.addEventListener("submit", async (event) => {
    event.preventDefault();
    if (requestInProgress) {
      return;
    }

    const cpu = Number(form.dataset.cpu);
    const block = memoryBlocks.get(form.elements.block.value);
    const word = Number(form.elements.word.value);
    const operation = operationSelect.value;
    const value = Number(form.elements.value.value);

    if (!block) {
      form.elements.block.setCustomValidity("Selecciona un bloque de memoria.");
      form.elements.block.reportValidity();
      return;
    }

    if (operation === "write" && (!Number.isSafeInteger(value) || value < 0)) {
      form.elements.value.setCustomValidity("Escribe un entero no negativo.");
      form.elements.value.reportValidity();
      return;
    }

    form.elements.block.setCustomValidity("");
    form.elements.value.setCustomValidity("");
    requestInProgress = true;
    setFormsDisabled(true);



    try {
      document.querySelector(`#cache${cpu+1}-title`).scrollIntoView({ behavior: 'smooth', block: 'start' });
      const message = await executeRequest(cpu, block, word, operation, value);
      renderCaches();
      showStep(message);
    } finally {
      setFsmState(cpu, "Idle");
      setFsmState(1 - cpu, "Idle");
      requestInProgress = false;
      setFormsDisabled(false);
    }
  });

  form.elements.value.addEventListener("input", () => {
    form.elements.value.setCustomValidity("");
  });
}

memoryToggle.addEventListener("click", () => {
  const isExpanded = memoryToggle.getAttribute("aria-expanded") === "true";
  memoryPanel.hidden = isExpanded;
  layout.classList.toggle("without-memory", isExpanded);
  document.querySelector(".status-panel").classList.toggle("without-memory", isExpanded);
  memoryToggle.setAttribute("aria-expanded", String(!isExpanded));
  memoryToggle.textContent = isExpanded ? "Mostrar memoria" : "Ocultar memoria";
});

for (let cpu = 0; cpu < caches.length; cpu += 1) {
  setFsmState(cpu, "Idle");
}

renderCaches();
