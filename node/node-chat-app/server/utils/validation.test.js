const expect = require('expect');
const {isRealString} = require('./validation');

describe('isRealString', () => {
    it('should reject non-string values', () => {
        let param = 123;
        let isValid = isRealString(param);
        expect(isValid).toBe(false);
    });
    it('should reject string with only spaces', () => {
        let param = '   ';
        let isValid = isRealString(param);
        expect(isValid).toBe(false);
    });
    it('should allow string with non-space characters', () => {
        let param = '   vim   ';
        let isValid = isRealString(param);
        expect(isValid).toBe(true);
    });
});
