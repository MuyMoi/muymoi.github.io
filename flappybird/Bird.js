class Bird {
	x; //normalmente no se modifica
	y;
	encaida;
	ensalto;
	vel;
	width;
	height;
	animid;
	velf_caida;
	velf_salto;
	veli_caida;
	veli_salto;

	constructor() {
		this.element = document.createElement("img");
		this.element.src = "images/flappy1.svg";
		this.element.style.position = "absolute";
		this.element.draggable = false;

		document.body.appendChild(this.element);

		//this.promise = new Promise();
	}

	/*setOpciones(bitcaida, bitsalto) {
		if (bitcaida ==true && bitsalto == true) {
			console.log("config no valida");
			return;
		}

		if (bitcaida == true) {
			this.debecaer = true;
			this.caer();
		} else if (bitcaida == false){
			this.debecaer = false;
		} // de lo contrario, no se modifica

		if (bitsalto == true) {
			this.debesaltar = true;
			this.saltar();
		} else if (bitsalto == false){
			this.debesaltar = false;
		}
	}*/

	pausar() {
		window.cancelAnimationFrame(this.animid);
	}

	reanudar() {
		if (this.ensalto) {
			this.debesaltar = true;
			this.animsaltar();
		}
		if (this.encaida) {
			this.debecaer = true;
			this.animcaer();
		}
	}

	posicionarX() {
		this.element.style.left = `${this.x}px`;
	}
	posicionarY() {
		this.element.style.transform = `translateY(${this.y}px)`;
	}

	setaltura(h) {
		//this.width = w;
		let w = h*1.51
		this.height = h;
		this.width = w;
		this.element.height = h + "";
		this.element.width = w + "";

		this.velf_caida = 0.3 * h;
		this.velf_salto = 0.03 * h;
		this.veli_caida = 0.03 * h;
		this.veli_salto = 0.3 * h;
	}

	mostrar() {
		this.element.hidden = false;
	}

	ocultar() {
		this.element.hidden = true;
	}

	setpos(_x, _y) {
		this.x = _x;
		this.y = _y;
		this.posicionarX();
		this.posicionarY();
	}

	rotar(grados) {
		this.element.style.transform += ` rotate(${grados}deg)`;
		//ojo que el metodos posicionarY anula la rotacion
	}

	moverX(n) {
		this.x += n;
		this.posicionarX();
	}
	
	moverY(n, grados) { //permite mover y rotar a la vez
		this.y += n;
		this.posicionarY();
		this.rotar(grados);
	}

	animcaer() {
		let angulo = (this.vel/this.velf_caida) * 50
		this.moverY(this.vel, angulo);

		if (this.vel < this.velf_caida)
			this.vel *= 1.125;

		this.animid = window.requestAnimationFrame( ()=> this.animcaer() )

	}

	caer() {
		this.pausar();

		this.vel = this.veli_caida;
		this.encaida = true;
		this.ensalto = false;
		this.animcaer();
	}

	animsaltar() {		//animacion de saltar
		let angulo = (this.vel/this.veli_salto) * 50;
		this.moverY(-this.vel, -angulo);

		if (this.vel >= this.velf_salto) {
			this.vel *= 0.9;
		}
		else {
			this.caer();
			return;
		}

		this.animid = window.requestAnimationFrame( ()=> this.animsaltar() )
	}

	saltar() {
		this.pausar();

		this.vel = this.veli_salto;
		this.ensalto = true;
		this.encaida = false;
		this.animsaltar();
	}
}