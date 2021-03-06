import { Component, OnInit, EventEmitter, Output } from '@angular/core';

@Component({
  selector: 'app-cockpit',
  templateUrl: './cockpit.component.html',
  styleUrls: ['./cockpit.component.css']
})

export class CockpitComponent implements OnInit {
  //newServerName = '';
  newServerContent = '';
  @Output() serverCreated = new
  EventEmitter<{serverName: string, serverContent: string}>();
  @Output() blueprintCreated = new
  EventEmitter<{bpName: string, bpContent: string}>();

  onAddServer(nameInput: HTMLInputElement) {
    console.log(nameInput);
    this.serverCreated.emit({
      serverName: nameInput.value,
      serverContent: this.newServerContent
    });
  }

  onAddBlueprint(nameInput: HTMLInputElement) {
    this.blueprintCreated.emit({
      bpName: nameInput.value,
      bpContent: this.newServerContent
    });
  }

  constructor() { }

  ngOnInit() {
  }

}
