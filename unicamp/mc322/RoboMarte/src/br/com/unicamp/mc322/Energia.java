package br.com.unicamp.mc322;

class Energia {

	private int energia;

	public Energia() {
		this.carregar(null);
	}

	public void carregar(Antena antena) {
		try {
			if (energia < 100) {
				if (antena != null) {
					antena.enviarMsg("Carregando energia...aguarde");
				}
				Thread.sleep(10);
				energia = 100;
				if (antena != null) {
					antena.enviarMsg("Carregado...");
				}
			} else {
				if (antena != null) {
					antena.enviarMsg("Ja estava carregado");
				}
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	public int possoAndar(int nPassos, Antena antena) {
		if (nPassos > 100) {
			return 0;
		}

		if (energia < nPassos) {
			this.carregar(antena);
		}

		energia = energia - nPassos;

		return nPassos;
	}
}
