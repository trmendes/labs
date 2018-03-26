import { Component, OnInit, Input } from '@angular/core';

@Component({
  selector: 'app-server-element',
  templateUrl: './server-element.component.html',
  styleUrls: ['./server-element.component.css']
})
export class ServerElementComponent implements OnInit {
  /* To expose this property to the word we need to user Input() */
  @Input('srvElement') element: {type: String, name: String, content: String};

  constructor() { }

  ngOnInit() {
  }

}
