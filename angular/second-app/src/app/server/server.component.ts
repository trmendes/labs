import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-server',
  templateUrl: './server.component.html',
  styleUrls: ['./server.component.css']
})
export class ServerComponent implements OnInit {

  serverId = 10;
  serverStatus = 'offilne';
  allowNewServer = false;

  getServerStatus() {
    return this.serverStatus;
  }

  constructor() {
    setTimeout(() => {
      this.allowNewServer = true;
      console.log(this.allowNewServer);
    }, 2000);
  }

  ngOnInit() {
  }

}
