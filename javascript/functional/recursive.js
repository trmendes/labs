let countDownFrom = (num) => {
    console.log(num);
    if (num == 0)
        return;
    countDownFrom(num - 1);
}

countDownFrom(10);


let categories = [
    { id: "animals", parent: null },
    { id: "mammals", parent: 'animals' },
    { id: "cats", parent: 'mammals' },
    { id: "dogs", parent: 'mammals' },
    { id: "chihuahua", parent: 'dogs' },
    { id: "labrador", parent: 'dogs' },
    { id: "persian", parent: 'cats' },
    { id: "siamese", parent: 'cats' }
]

let makeTree = (categories, parent) => {
    let node = {};
    categories.
        filter(c => c.parent === parent).
        forEach(c => node[c.id] = makeTree(categories, c.id));
    return node;
}

newJson = makeTree(categories, null);
console.dir(newJson, {colors: true});
console.log(JSON.stringify(newJson, null, 2));
