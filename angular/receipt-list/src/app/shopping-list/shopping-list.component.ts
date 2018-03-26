import { Component, OnInit } from '@angular/core';

import { Recipe } from '../recipes/recipe.model';

@Component({
  selector: 'app-shopping-list',
  templateUrl: './shopping-list.component.html',
  styleUrls: ['./shopping-list.component.css']
})
export class ShoppingListComponent implements OnInit {
  recipes: Recipe[] = [
    new Recipe('Test Recipe', 'This is just a test',
      'https://en.wikipedia.org/wiki/Pamonha#/media/File:Pamonhas.jpg')
  ];

  constructor() { }

  ngOnInit() {
  }

}
