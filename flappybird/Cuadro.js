class Cuadro {
  div; style; id; elementos = [];
  constructor(id, alto, ancho, centrado) {
    this.id = "#" + id;
    this.div = document.createElement("div");
    this.div.id = id;
    this.div.className = "cajas";
    this.style = this.div.style;

    /*this.style.height = alto;
    this.style.width = ancho;*/

    this.settam(alto, ancho);
    this.setpos("50%", "50%");

    if (centrado)
      this.style.transform = "translate(-50%,-50%)";
  }
  crearElemento(tipoElem, texto) {
    const elem = document.createElement(tipoElem);
    elem.innerHTML = texto;
    this.div.appendChild(elem);
    return elem;
  }
  settam(alt, anc) {
    this.style.height = (typeof alt == "number") ? alt+"px" : alt;
    this.style.width = (typeof anc == "number") ? anc+"px" : anc;
  }
  setpos(l,t) {
    this.style.left = (typeof l == "number") ? l+"px" : l;
    this.style.top = (typeof t == "number") ? t+"px" : t;
  }
  setatributo(atr, valor) {
    this.style[atr] = valor;
  }
  crearBoton(texto, tipoevento, accion) {
    const boton = document.createElement("button");
    boton.textContent = texto;
    boton["on" + tipoevento] = accion;
    boton.className = "acc";
    this.div.appendChild(boton);
    return boton;
  }

  cerrar() {
    this.div.remove();
  }
  mostrar() {
    if (!document.querySelector(this.id)) {
      document.body.appendChild(this.div);
    } else {
      this.cerrar();
    }
  }
}