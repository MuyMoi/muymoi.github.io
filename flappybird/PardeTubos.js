class PardeTubos {
	x;
	y1;	// coord del tubo de arriba
	y2;	// coord del tubo de abajo
	vel;
	width;
	e1 = document.createElement("img");
	e2 = document.createElement("img");
	animid;
	sep;

	constructor(ancho, separacion) {
		this.e1.src = this.e2.src = "images/tubo.png";
		this.e1.height = this.e2.height = window.innerHeight;
		this.e1.style["position"] = this.e2.style["position"] = "absolute";
		this.e1.draggable = this.e2.draggable = false;

		this.sep = separacion;
		this.setancho(ancho);
		this.setdimensiones();

	}

	setdimensiones() {
		let h = window.innerHeight;

		this.y2 =
			Math.floor(Math.random() *
			(window.innerHeight-this.sep*1.5)) + this.sep + 20;
		this.y1 = this.y2 - this.sep;

		this.e2.style.top = `${this.y2}px`;
		this.e1.style.top = `${this.y1 - h}px`;

		this.x = window.innerWidth;

		this.mover();
		document.body.appendChild(this.e1);
		document.body.appendChild(this.e2);
	}

	setancho(w) {
		this.width = w;
		this.e1.width = this.e2.width = w;

		this.vel = w / 10;
	}

	mover() {
		this.x -= this.vel;
		this.e1.style.transform = this.e2.style.transform = `translateX(${this.x}px)`;
	}

	/*/pausar() {
		window.cancelAnimationFrame(this.animid);
	}*/

	reanudar() {
		this.mover();
	}

	destructor() {
		//this.pausar();
		//this.mover = () => {}; //importante: así evito que se pueda invocar
		//el metodo mover desde afuera cuando se ejecute el destructor
		//y evita errores donde mover se seguia ejecutando a pesar de
		//haber hecho los atributos e1 y e2 = null
		this.e1.remove();
		this.e1 = null;
		this.e2.remove();
		this.e2 = null;
	}
}