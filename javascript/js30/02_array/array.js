'use strict';

const people = [
    {id: 0, name: 'Roberto', year: 1980 },
    {id: 1, name: 'Marcelo', year: 1980 },
    {id: 2, name: 'Ana', year: 2000 },
    {id: 3, name: 'Diego', year: 1999 },
    {id: 4, name: 'Maria', year: 2005 },
    {id: 5, name: 'Marina', year: 2010 },
    {id: 6, name: 'Marcela', year: 1960 },
    {id: 7, name: 'Rafaela', year: 1979 },
    {id: 8, name: 'Camila', year: 2000 },
    {id: 9, name: 'Jose', year: 2000 },
    {id: 10, name: 'Rodolfo', year: 2001 }
];

const comments = [
    {text: 'Uhu!', id: 12365 },
    {text: 'Rapel!', id: 234093 },
    {text: 'Come on!', id: 999333 },
    {text: 'The number of the beast', id: 666999 },
    {text: 'Lets turn frustration into inspiration', id: 764097  },
    {text: 'Start wearing purple', id: 357344 }
];

// SOME----------------------------------
// It will return true or false
// True: If at least one element has year === 2000
const retSome = people.some(e => e.year === 2000);
console.log(`Some returns ${retSome}`);

// EVERY---------------------------------
// It will return true in case every element.year === 2000
let retEvery = people.every(e => e.year === 2000);
console.log('Every returns: ', retEvery);
// It will return true in case every element.year < 2020
retEvery = people.every(e => e.year < 2020);
console.log('Every returns: ', retEvery);

// FIND---------------------------------
// It will return the first element that matches the year === 2000
const retFind = people.find(e => e.year === 2000);
console.log('Find returns: ', retFind);

// FILTER-------------------------------
// It will return all the elements that matches the year === 1980
const retFilter = people.filter(e => e.year === 1980);
console.log('Filter returns: ', retFilter);

// FINDINDEX ---------------------------
// It will return the index of the first element that matches the year === 2000
const retFindIdx = people.findIndex(e => e.year === 2000);
console.log('Find Index returns: ', retFindIdx);

// MAP ---------------------------------
// It will return a new Array containing the returned elements the function
// we pass to map
const retMap = people.map(e => e.name);
console.log('Map returns: ', retMap);

// REDUCE ------------------------------
// Apply a function againt an accumulator and each element in the array
// to reduce it to a single value
const retReduce = people.reduce((accumulator, curValue) => accumulator +
    curValue.id, 0);
console.log('Reduce returns: ', retReduce);

// SLICE ------------------------------
// It will return a shallow copy of a portion of an array
// the 1th param is the start idx (including it)
// the 2th param is the end idx (does not include it)
let retSlice = people.slice(2, 5);
console.log('Slice returns: ', retSlice);

// FROM idx 2 to idx = array.length - 2 (it will skip the last el)
retSlice = people.slice(2, -1);
console.log('Slice returns: ', retSlice);

// SORT ------------------------------
// SORT BY ID DESC
people.sort((eA, eB) => eB.id - eA.id);
console.log('Sort does: ', people);
// SORT BY NAME
people.sort((eA, eB) => {
    const nameA = eA.name.toUpperCase();
    const nameB = eB.name.toUpperCase();
    if (nameA < nameB) {
        return -1;
    }
    if (nameA > nameB) {
        return 1;
    }
    return 0;
});
console.log('Sort does: ', people);

// SORT BY YEAR ASC
people.sort((eA, eB) => eA.year - eB.year);
console.log('Sort does: ', people);


// SPLICE---------------------------
// CHANGES THE CONTENT OF AN ARRAY BY ADDING OR REMOVING ELEMENTS
// This will remove 2 elements from the position 1
people.sort((eA, eB) => eA.id - eB.id);
//console.log('before splice: ', people);
//people.splice(2, 4);
//console.log('after splice: ', people);
console.table('before splice: ', people);
// Start at the end of the array
people.splice(-2, 4);
console.table('after splice: ', people);



