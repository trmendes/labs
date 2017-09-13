package br.com.unicamp.mc322;

import java.util.Scanner;

public class ContoleRobo {

	private static Scanner reader;

	public static void main(String[] args) {
		Robo robo = new Robo();
		int rInput;
		int passos;
		imprimirMenu();
		reader = new Scanner(System.in);
		
		while (true) {
			rInput = reader.nextInt();
			System.out.println("Entrada do operador: " + rInput);
			switch (rInput) {
			case 0:
				imprimirMenu();
				break;
			case 1:
				robo.getMinhaPosicao();
				break;
			case 2:
				robo.recarregar();
				break;
			case 3:
				robo.getDirecao();
				break;
			case 4:
				System.out.print("-> Direcao: " );
				robo.getDirecao();
				System.out.println("Quantos passos para esta direcao?: ");
				passos = reader.nextInt();
				System.out.println("Entrada do operador: " + passos + " passos");
				robo.andar(passos);
				break;
			case 5:
				robo.girarEsq();
				robo.getDirecao();
				break;
			case 6:
				robo.girarDir();
				robo.getDirecao();
				break;
			case 7:
				return;
			}
		}
		
	}
	
	public static void imprimirMenu() {
		System.out.println("0) Imprimir este menu");
		System.out.println("1) Imprimir mapa de marte");
		System.out.println("2) Recarregar bateria");
		System.out.println("3) Consultar direcao");
		System.out.println("4) Andar x passos");
		System.out.println("5) Girar para a esquerda");
		System.out.println("6) Girar para a direita");
		System.out.println("7) Desligar o robo");
	}

}
