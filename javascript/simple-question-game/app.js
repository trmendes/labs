(function() {
    let sc = 0;
    let idx;
    let getUserInput;
    let userInput;
    let userInputN;
    let questions = [];
    let Question;

    function init() {
        Question = function(question, answers, correctIdx) {
            this.question = question;
            this.answers = answers; // Clone it
            this.correctIdx = correctIdx;
            this.printQuestion = function() {
                console.log(this.question);
            };
            this.printAnswers = function() {
                let idx = 0;
                this.answers.forEach(function(ans) {
                    console.log('%d - %s', idx, ans);
                    ++idx;
                });
            };
        };

        questions = [
            new Question(
                'What is the oldest ant in the anthill?',
                ['What the fuck?!',
                    'The one with a white antenna',
                    'The ant queen'],
                0),
            new Question(
                'What is the capital of Brazil?',
                ['Buenos Aires',
                    'Rio de Janeiro',
                    'Sao Paulo',
                    'Lima',
                    'Brasilia'],
                4),
            new Question(
                'Is privacy important?',
                ['yes', 'are you serious?'],
                0)];
    }

    function score() {
        let score = 0;
        return function(correct) {
            if (correct) {
                ++score;
                console.log('\\o/');
            } else {
                console.log('Wrong answer /o\\');
            }
            return score;
        }
    }

    let updateScore = score();

    function showNextQuestion() {
        idx = Math.floor(Math.random() * questions.length);
        questions[idx].printQuestion();
        questions[idx].printAnswers();
    }

    init();
    while (true) {
        showNextQuestion();
        getUserInput = () => prompt("So the correct answer is? :O");
        userInput = getUserInput();
        userInputN = parseInt(userInput, 10);
        if (isNaN(userInput)) {
            break;
        } else {
            sc = updateScore(userInputN === questions[idx].correctIdx);
            console.log('Your score: %d', sc);
            console.log('---------------------------------------------');
        }
    }
})();


