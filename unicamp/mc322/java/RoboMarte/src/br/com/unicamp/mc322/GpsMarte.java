package br.com.unicamp.mc322;

class GpsMarte {

	private int[][] superficieMapa = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0 },
			{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0 },
			{ 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
			{ 1, 1, 2, 2, 2, 3, 3, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0 },
			{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

	private int x;
	private int y;

	private final int livre = 0;
	private final int pedra = 1;
	private final int montanha = 2;
	private final int buraco = 3;

	public GpsMarte() {
		x = 0;
		y = 0;
	}

	public String imprimirSuperficie() {
		String msg = "";
		int i, j;
		System.out.println("x " + x + " | y " + y);
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 17; j++) {
				if ((x == j) && (y == i)) {
					msg = msg + "RB";
				} else {
					if (this.superficieMapa[i][j] == this.livre)
						msg = msg + "__";
					else if (this.superficieMapa[i][j] == this.pedra)
						msg = msg + "**";
					else if (this.superficieMapa[i][j] == this.montanha)
						msg = msg + "/\\";
					else if (this.superficieMapa[i][j] == this.buraco)
						msg = msg + "[]";
				}
			}
			msg = msg + "\n";
		}
		return msg;
	}

	public int andar(int angulo, int nPassos) {
		int j, andado = 0;
		switch (angulo) {
		case 180: // frente
			for (j = x; j < nPassos && x < 16 ; j++, x++) {
				if (superficieMapa[y][x] != this.livre) {
					x--;
					break;
				}
				else {
					++andado;					
				}
				
			}
			break;
		case 360: // tras
			for (j = x; j < nPassos && x > 0; j++, x--) {
				if (superficieMapa[y][x] != this.livre) {
					x++;
					break;
				}
				else
					++andado;
				if (andado == nPassos)
					break;
			}
			break;
		case 90:// cima0
			for (j = y; j < nPassos && y > 0; j++, y--) {
				if (superficieMapa[y][x] != this.livre) {
					y++;
					break;
				}
				else
					++andado;
				if (andado == nPassos)
					break;
			}
			break;
		case 240: // baixo
			for (j = y; j < nPassos && y < 7; j++, y++) {
				if (superficieMapa[y][x] != this.livre) {
					y--;
					break;
				}
				else
					++andado;
				if (andado == nPassos)
					break;
			}
			break;
		}

		return andado;
	}
}