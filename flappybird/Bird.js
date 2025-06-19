class Bird {
	x; //normalmente no se modifica
	y;
	debecaer;
	debesaltar;
	encaida;
	ensalto;
	vel;
	width = 50;
	height = 33;

	constructor() {
		this.element = document.createElement("img");
		this.element.src = "flappy1.svg";
		this.element.width = this.width + "";
		this.element.height = this.height + "";
		this.vel = 1;

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
		this.debesaltar = false;
		this.debecaer = false;
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
		// rotar en una proporcion 5 veces la velocidad
		this.moverY(this.vel, this.vel*5);
		if (this.vel < 10)
			this.vel *= 1.125;

		if (this.debecaer)
			window.requestAnimationFrame( ()=> this.animcaer() )

	}

	caer() {
		this.debesaltar = false;
		this.ensalto = false;
		if ( !this.encaida ) {  //si no hay un proceso de caida activo
			this.vel = 1;
			this.debecaer = true;
			this.encaida = true;
			this.animcaer();
		}

	}

	animsaltar() {		//animacion de saltar
		this.moverY(-this.vel, -this.vel*5);
		
		if (this.vel >= 1) {
			this.vel *= 0.9;
		}
		else {
			this.caer();
			return;
		}

		if (this.debesaltar)
			window.requestAnimationFrame( ()=> this.animsaltar() )
	}

	saltar() {
		this.vel = 12;
		this.debecaer = false;
		this.encaida = false;
		
		if ( !this.ensalto ) {  //si no hay un proceso de salto activo
			this.ensalto = true;
			this.debesaltar = true;
			this.animsaltar();
		}
	}
}