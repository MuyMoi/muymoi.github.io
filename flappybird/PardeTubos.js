class PardeTubos {
	x;
	y1;	// coord del tubo de arriba
	y2;	// coord del tubo de abajo
	vel = 5;
	width = 50;
	debedetener;
	e1 = document.createElement("img");
	e2 = document.createElement("img");

	constructor() {
		this.debedetener = true;

		this.e1.src = this.e2.src = "tubo.png";
		this.e1.width = this.e2.width = this.width;
		this.e1.height = this.e2.height = window.innerHeight;
		this.e1.style["position"] = this.e2.style["position"] = "absolute";
	}

	init() {
		document.body.appendChild(this.e1);
		document.body.appendChild(this.e2);

		let h = window.innerHeight;
		let sep= 130;

		this.y2 = Math.floor(Math.random() * (window.innerHeight-sep*1.5)) + sep + 20;
		this.y1 = this.y2 - sep;

		this.e2.style.top = `${this.y2}px`;
		this.e1.style.top = `${this.y1 - h}px`;

		this.x = window.innerWidth;
		this.posicionarX();

		this.debedetener = false;
		this.mover();
	}

	posicionarX() {
		//this.e1.style.left = this.e2.style.left = `${this.x}px`;
		this.e1.style.transform = this.e2.style.transform = `translateX(${this.x}px)`;
	}



	mover() {
		this.x -= this.vel;
		this.posicionarX();

		if (!this.debedetener)
			window.requestAnimationFrame(()=> this.mover());
	}

	pausar() {
		this.debedetener = true;
	}

	reanudar() {
		this.debedetener = false;
		this.mover();
	}

	destructor() {
		this.debedetener = true;
		this.mover = () => {}; //importante: así evito que se pueda invocar
		//el metodo mover desde afuera cuando se ejecute el destructor
		//y evita errores donde mover se seguia ejecutando a pesar de
		//haber hecho los atributos e1 y e2 = null
		this.e1.remove();
		this.e1 = null;
		this.e2.remove();
		this.e2 = null;
	}
}