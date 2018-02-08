class Park {
    constructor(name, buildYear, area, numberOfTrees = 10) {
        this.name = name;
        this.buildYear = buildYear;
        this.area = area;
        this.numberOfTrees = numberOfTrees;
    }
    getName() {
        return this.name;
    }
    getBuildYear() {
        return this.buildYear;
    }
    getArea() {
        return this.area;
    }
    getNumberOfTress() {
        return this.numberOfTrees;
    }
    getTreeDensity() {
        return parseInt((this.numberOfTrees / this.area) * 100);
    }
};

class Street {
    constructor(name, buildYear, size = 10) {
        this.name = name;
        this.buildYear = buildYear;
        this.size = size;
    }
    getName() {
        return this.name;
    }
    getBuildYear() {
        return this.buildYear;
    }
    getSize() {
        return this.size;
    }
};

class City {
    constructor(name) {
        this.name = name;
        this.parks = [
            new Park('Park A', 1900, 1000),
            new Park('Park B', 2000, 4000, 2000),
            new Park('Park C', 2016, 6000, 5000)
        ];
        this.streets = [
            new Street('Street A', 1950),
            new Street('Street B', 1951, 20),
            new Street('Street C', 1952),
            new Street('Street D', 1953, 20)
        ];
    }
    getName() {
        return this.name;
    }
    getParks() {
        return this.parks;
    }
    getStreets() {
        return this.streets;
    }
};

let parksReport = (parks) => {
    return {
        treeDensity: (() => {
            let tDens = [];
            parks.forEach((park) => {
                tDens.push({
                    name: park.getName(),
                    density: park.getTreeDensity()
                });
            });
            return tDens;
        })(),
        parkAvgAge: (() => {
            let ageSum = 0;
            parks.forEach((park) => {
                ageSum += park.getBuildYear();
            });
            return 2018 - (ageSum / parks.length);
        })(),
        greenParks: (() => {
            const names = [];
            parks.forEach((park) => {
                if (park.getNumberOfTress() > 1000) {
                    names.push({name: park.getName()});
                }
            });
            return names;
        })()
    }
};

let streetReports = (streets) => {
    return {
        streenData: (() => {
            let total = 0;
            streets.forEach((street) => {
                total += street.getSize();
            });
            return {
                total: total,
                avg: total / streets.length
            };
        })()
    }
};

const city = new City('jsTown');

pReport = parksReport(city.getParks());
sReport = parksReport(city.getStreets());

console.log('-----PARKS REPORT------');
console.log(`Our ${city.getParks().length} have an avarage of ${pReport.parkAvgAge} years.`);
pReport.treeDensity.forEach((p) => {
    console.log(`${p.name} has a tree density of ${p.density}%`);
});
pReport.greenParks.forEach((p) => {
    console.log(`${p.name} has more than 1000 trees.`);
});
console.log('-----STREETS REPORT------');
console.log(`Our ${city.getStreets().length} streets have a total length of ${sReport.streetData.total} km, with an avarage of ${sReport.streenData.avg} km`);
