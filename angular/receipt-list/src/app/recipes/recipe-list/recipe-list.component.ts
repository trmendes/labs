import { Component, OnInit } from '@angular/core';

import { Recipe } from '../recipe.model';

@Component({
  selector: 'app-recipe-list',
  templateUrl: './recipe-list.component.html',
  styleUrls: ['./recipe-list.component.css']
})
export class RecipeListComponent implements OnInit {
  recipes: Recipe[] = [
    new Recipe('Test Recipe', 'This is just a test',
      'https://upload.wikimedia.org/wikipedia/commons/thumb/b/b7/Pamonhas.jpg/500px-Pamonhas.jpg'),
		new Recipe('Test Recipe 2', 'This is just a second test',
			'https://3.bp.blogspot.com/-IkXXpkCnu8c/Uaqsw2DuFNI/AAAAAAAAAS8/QwIfMdxXWYc/s1600/receita-curau-eduardo-delfim.jpg')
  ];

  constructor() { }

  ngOnInit() {
  }

}
