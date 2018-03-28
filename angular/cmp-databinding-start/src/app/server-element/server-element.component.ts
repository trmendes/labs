import {
  Component,
  OnInit,
  Input,
  ViewEncapsulation,
  OnChanges,
  SimpleChanges,
  DoCheck,
  AfterContentInit,
  AfterContentChecked,
  AfterViewInit,
  AfterViewChecked,
  OnDestroy
} from '@angular/core';

@Component({
  selector: 'app-server-element',
  templateUrl: './server-element.component.html',
  styleUrls: ['./server-element.component.css']
})

export class ServerElementComponent implements OnInit, OnChanges, DoCheck,
  AfterContentInit, AfterContentChecked,
  AfterViewInit, AfterViewChecked, OnDestroy {
    /* To expose this property to the word we need to user Input() */
    @Input('srvElement') element: {type: string, name: string, content: string};
    public time = 0;
    public constructorCalls = 0;
    public onInitCalls = 0;
    public onChangeCalls = 0;
    public onDoCheckCalls = 0;
    public onAfterCntInitCalls = 0;
    public onAfterCntCheckCalls = 0;
    public onAfterViewInitCalls = 0;
    public onAfterViewCheckedCalls = 0;
    public onDestroyCalls = 0;

    constructor() {
      console.log(`${this.time} --> Constructor called`);
      console.log(`Calls to this function: ${this.constructorCalls}`);
      ++this.constructorCalls;
      ++this.time;
    }

    ngOnInit() {
      console.log(`${this.time} --> ngOnInit called`);
      console.log(`Calls to this function: ${this.onInitCalls}`);
      ++this.constructorCalls;
      ++this.time;
    }

    ngOnChanges(changes: SimpleChanges) {
      console.log(`${this.time} --> ngOnChange called`);
      console.log(`Calls to this function: ${this.onChangeCalls}`);
      ++this.onChangeCalls;
      ++this.time;
      console.log(changes);
    }

    ngDoCheck() {
      console.log(`${this.time} --> ngDoCheck called`);
      console.log(`Calls to this function: ${this.onDoCheckCalls}`);
      ++this.onDoCheckCalls;
      ++this.time;
    }

    ngAfterContentInit() {
      console.log(`${this.time} --> ngAfterContentInit called`);
      console.log(`Calls to this function: ${this.onAfterCntInitCalls}`);
      ++this.onAfterCntInitCalls;
      ++this.time;
    }

    ngAfterContentChecked() {
      console.log(`${this.time} --> ngAfterContentChecked called`);
      console.log(`Calls to this function: ${this.onAfterCntCheckCalls}`);
      ++this.onAfterCntCheckCalls;
      ++this.time;
    }


    ngAfterViewInit() {
      console.log(`${this.time} --> ngAfterViewInit called`);
      console.log(`Calls to this function: ${this.onAfterViewInitCalls}`);
      ++this.onAfterViewInitCalls;
      ++this.time;
    }

    ngAfterViewChecked() {
      console.log(`${this.time} --> ngAfterViewChecked called`);
      console.log(`Calls to this function: ${this.onAfterViewCheckedCalls}`);
      ++this.onAfterViewCheckedCalls;
      ++this.time;
    }

    ngOnDestroy() {
      console.log(`${this.time} --> ngOnDestroy called`);
      console.log(`Calls to this function: ${this.onDestroyCalls}`);
      ++this.onDestroyCalls;
      ++this.time;
    }

  }
