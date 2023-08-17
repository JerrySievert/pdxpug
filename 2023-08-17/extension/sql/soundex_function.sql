CREATE EXTENSION soundex;

-- john and joan should be similar
SELECT soundex('john');
SELECT soundex('joan');

-- principally is a longer word
SELECT soundex('principally');

-- there, their, and they're should match
SELECT soundex('there') = soundex('their') AND soundex('they''re') = soundex('there');
