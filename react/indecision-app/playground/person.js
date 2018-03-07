class Person {
    constructor(name = 'Anonymous', age = 0) {
        this.name = name;
        this.age = age;
    }
    getGretting() {
        return `Hi. I am ${this.name}`;
    }
    getDescription() {
        return `${this.name} is ${this.age} year(s) old.`;
    }
}

class Student extends Person {
    constructor(name, age, major = 'None') {
        super(name, age);
        this.major = major;
    }
    getDescription() {
        return super.getDescription() + ` - Major ${this.major}`;
    }
}

class Traveler extends Person {
    constructor(name, age, homeLocation) {
        super(name, age);
        this.home = homeLocation;
    }

    getGretting() {
        if (this.home) {
            return super.getGretting() + ` from ${this.home}`;
        }
        return  super.getGretting();
    }
}

const me = new Traveler('jose', 21, 'Portugal');
console.log(me);
console.log(me.getGretting());
