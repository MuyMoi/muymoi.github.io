const amp = document.getElementById('ampliado');
const elementos = document.querySelectorAll(".elem");


function ampliar() {
	const est = getComputedStyle(this);
	let left = Math.ceil(parseFloat(est.left) * 3);
	let top = Math.ceil(parseFloat(est.top) * 3);
	amp.style.background = `url('tablaperiodica.png') -${left}px -${top}px`;
}

for (let index = 0; index < 118; index++) {
    elementos[index].onclick = ampliar;
}
window.onload = function () {
	if (document.querySelector("#contenedortp > p") === null) {
		document.write("No se puede ver la pagina porque no se le han dado creditos al autor del contenido.")
	}
}