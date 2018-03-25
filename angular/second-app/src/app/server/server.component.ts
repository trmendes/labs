import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-server',
  templateUrl: './server.component.html',
  styleUrls: ['./server.component.css']
})
export class ServerComponent implements OnInit {

  serverId: Number = 10;
  serverName: String = 'server_name';
  serverStatus: String = 'offilne';
  serverCreationStatus: String = 'No server was created!';
  allowNewServer: Boolean = false;
  serverCreated: Boolean = false;

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

  onCreateServer() {
    this.serverCreated = true;
    this.serverCreationStatus = `\\o/ Server was created! Name:
    ${this.serverName}`;
    this.serverStatus = 'online';
  }

  onUpdateServerName(event: any) {
    this.serverName = (<HTMLInputElement> event.target).value;
  }

}
