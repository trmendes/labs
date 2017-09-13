package br.com.unicamp.mc322;

class Roda {
	private int angulo;

	public Roda() {
		this.angulo = 180;
	}

	public int getAngulo() {
		return this.angulo;
	}

	public void girarEsq() {
		switch (this.angulo) {
		case 180:
			angulo = 90;
			break;
		case 360:
			angulo = 240;
			break;
		case 90:
			angulo = 360;
			break;
		case 240:
			angulo = 180;
			break;
		}
	}

	public void girarDir() {
		switch (this.angulo) {
		case 180:
			angulo = 240;
			break;
		case 360:
			angulo = 90;
			break;
		case 90:
			angulo = 180;
			break;
		case 240:
			angulo = 360;
			break;
		}
	}

	public String getDir() {
		switch (this.angulo) {
		case 180:
			return "Andando para frente\n";
		case 360:
			return "Andando para tras\n";
		case 90:
			return "Andando para cima\n";
		case 240:
			return "Andando para baixo\n";
		}
		return "Desconhecido";
	}
}
