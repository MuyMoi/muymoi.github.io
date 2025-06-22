"use strict"

class Bird {
	x; //normalmente no se modifica
	y;
	enpausa;
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
		this.enpausa = false;

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

	cancelar_anim() {
		window.cancelAnimationFrame(this.animid);
	}

	pausar() {
		this.enpausa = true;
		this.cancelar_anim();
	}

	reanudar() {
		this.enpausa = false;
		if (this.ensalto) {
			this.animsaltar();
		}
		if (this.encaida) {
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
		//console.log("inciiando caida")		///
		//console.log()

		this.cancelar_anim();
		this.vel = this.veli_caida;

		if (!this.enpausa) {
			this.encaida = true;
			this.ensalto = false;
			this.animcaer();
		}
	}

	animsaltar() {		//animacion de saltar
		let angulo = (this.vel/this.veli_salto) * 50;
		this.moverY(-this.vel, -angulo);

		if (this.vel > this.velf_salto) {
			this.vel *= 0.9;
		}
		else {
			//setTimeout(()=>this.caer(), 700); 		///
			this.caer()
			return;
		}

		this.animid = window.requestAnimationFrame( ()=> this.animsaltar() );
	}

	saltar() {
		this.cancelar_anim();
		this.vel = this.veli_salto;

		if (!this.enpausa) {
			this.ensalto = true;
			this.encaida = false;
			this.animsaltar();
		}
	}
}