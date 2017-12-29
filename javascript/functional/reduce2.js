var output = "person A\twaffle iron\t80\t2\n\
person A\tblender\t200\t1\n\
person A\tknife\t10\t4\n\
person B\twaffle iron\t80\t1\n\
person B\tknife\t10\t2\n\
person B\tpot\t20\t3".

    split("\n").
    map(line => line.split('\t')).
    reduce((persons, line) => {
        /* It will create a new person or use the one if exists */
        persons[line[0]] = persons[line[0]] || [];
        /* Start to create the json based on our array */
        persons[line[0]].push( {
            name: line[1],
            price: line[2],
            quantity: line[3]
        }
        );
        return persons;
    }, {});

console.log(JSON.stringify(output, null, 2));



