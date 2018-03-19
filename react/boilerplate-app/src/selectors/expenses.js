export default (expenses, { text, sortBy , startDate, endDate }) => {
    return expenses.filter((exp) => {

        const startDateMatch = typeof exp.startDate !== 'number' ||
            exp.startData >= startDate;

        const endDateMath = typeof exp.endDate !== 'number' ||
            exp.endDate <= endDate;

        const textMatch = exp.description.toLowerCase().includes(
            text.toLowerCase());

        return startDateMatch && endDateMath && textMatch;
    }).sort((a, b) => {
        if (sortBy === 'date') {
            return b.createdAt - a.createdAt;
        } else if (sortBy === 'amount') {
            return b.amount - a.amount;
        }
    });
};
