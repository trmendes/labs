const users = [{
        id: 1,
        name: 'Andrew',
        schoolId: 101
    },{
        id: 2,
        name: 'Jessica',
        schoolId: 999
    }
];

const grades = [{
        id: 1,
        schoolId: 101,
        grade: 86
    },{
        id: 2,
        schoolId: 999,
        grade: 100
    },{
        id: 3,
        schoolId: 101,
        grade: 80
    }
];

const getUser = id => {
    return new Promise((resolve, reject) => {
        const user = users.find(user => user.id === id);
        if (user) {
            resolve(user);
        } else {
            reject(`Unable to find user with id of ${id}`);
        };
    });
};

const getGrades = schoolId => {
    return new Promise((resolve, reject) => {
        resolve(grades.filter(grade => grade.schoolId === schoolId));
    });
};

/*
 * When using async we get a Promise back
 * resolve(the return)
 * return is the same as resolve
 * 'throw new Error' is the same as reject
 */
const getStatusAlt = async userId => {
    /* YOU MUST USE IT INSIDE OF AN ASYNC FUNC */

    // throw new Error('This is an error');
    // return 'Mike';
    const user = await getUser(userId);

    /* If getUser throw an error (a catch)
     * await will throw an error
     * if it is ok it goes to the next line
     */
    const grades = await getGrades(user.schoolId);

    const average = grades.map(grade => grade.grade).
        reduce((sum, value) => sum + value) / grades.length;
    return `${user.name} has a ${average}% in the class`;
};

getStatusAlt(1).then(data => {
    console.log(data);
}).catch(e => console.log(e));;
