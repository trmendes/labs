class Stark {
    name : string = 'Brandon';
    static castle : string = 'Winterfell';
    saying: string;
    constructor() {
        this.saying = 'Winterfell';
    }
    hello(person) {
        console.log('hello ', person);
    }
};

let ned = new Stark();
ned.saying = 'The winter is coming';
