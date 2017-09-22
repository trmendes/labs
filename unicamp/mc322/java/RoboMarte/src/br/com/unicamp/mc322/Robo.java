package br.com.unicamp.mc322;

class Robo {
	private GpsMarte gps;
	private Roda roda;
	private Energia energia;
	private Antena antena;

	public Robo() {
		gps = new GpsMarte();
		roda = new Roda();
		energia = new Energia();
		antena = new Antena();
	}
	
	public void andar(int nPassos) {
		int tenhoEnergiaPara = energia.possoAndar(nPassos, this.antena);
		
		if (tenhoEnergiaPara < nPassos) {
			antena.enviarMsg("Não tenho energia suficiente para andar tudo mas vou andar o quanto posso");
			antena.enviarMsg("Tenho energia para " + tenhoEnergiaPara + " passos.");
			antena.enviarMsg("---> Carregue o Robo <---");
		}
		
		int andado = gps.andar(this.roda.getAngulo(), tenhoEnergiaPara);
		if (andado == tenhoEnergiaPara) {
			antena.enviarMsg("Sucesso. Andei " + andado + " passos.");
		} else {
			antena.enviarMsg("Devido a alguma irregularidade no terreno...andei somente " + andado + " passos");
			antena.enviarMsg("Verifique o mapa para encontrar um outro caminho sem obstaculos");
		}
	}
	
	public void girarEsq() {
		roda.girarEsq();
	}
	
	public void girarDir() {
		roda.girarDir();
	}
	
	public void getMinhaPosicao() {
		antena.enviarMsg(gps.imprimirSuperficie());
	}
	
	public void recarregar() {
		energia.carregar(this.antena);
	}
	
	public void getDirecao() {
		antena.enviarMsg(roda.getDir());
	}
	
}