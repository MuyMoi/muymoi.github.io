class PardeTubos {
	x;
	y1;	// coord del tubo de arriba
	y2;	// coord del tubo de abajo
	vel;
	width;
	e1 = document.createElement("img");
	e2 = document.createElement("img");
	sep;

	constructor(ancho, separacion) {
		this.e1.src = this.e2.src = "images/tubo.png";
		this.e1.style["position"] = this.e2.style["position"] = "absolute";
		this.e1.draggable = this.e2.draggable = false;
    this.e1.oncontextmenu = this.e2.oncontextmenu = (e) => e.preventDefault();
		this.init(ancho, separacion);
	}

	setdimensiones(w) {
		let h = window.innerHeight;
		this.e1.height = this.e2.height = h;
		
		this.width = w;
		this.e1.width = this.e2.width = w;

		this.vel = w / 10;
	}

	setposAleatY() {
		let h = window.innerHeight;

		this.y2 =
			Math.floor(Math.random() *
			(window.innerHeight-this.sep*1.5)) + this.sep + 20;
		this.y1 = this.y2 - this.sep;

		this.e1.style.top = `${this.y1 - h}px`;
		this.e2.style.top = `${this.y2}px`;

	}

	setposX(_x) {
		this.x = _x;
		this.e1.style.transform = this.e2.style.transform = `translateX(${this.x}px)`;
	}

	init(ancho, separacion) {
		this.sep = separacion;

		this.setposAleatY();
		this.setdimensiones(ancho, separacion);
		
		let main = document.getElementById("main")
		main.style.height = (window.innerHeight ) + "px"
		main.style.width = (window.innerWidth) + "px"
		main.appendChild(this.e1);
		main.appendChild(this.e2);
	}

	mover() {
		this.x -= this.vel;
		this.e1.style.transform = this.e2.style.transform = `translateX(${this.x}px)`;
	}

	reanudar() {
		this.mover();
	}

	destructor() {
		this.e1.remove();
		this.e1 = null;
		this.e2.remove();
		this.e2 = null;
	}
}