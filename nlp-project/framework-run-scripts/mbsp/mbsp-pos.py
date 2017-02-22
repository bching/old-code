import MBSP

inpt = ""

with open('_raw/posCase-v5.txt', 'r') as f:
	inpt = f.read().replace('\n', ' ')

ustr = unicode(inpt,encoding="utf-8")

#tokenized_words = MBSP.tokenizer.split(ustr, tags=True, replace={}, ignore=[])
tokenized_words = MBSP.tag(ustr, tokenize=True, lemmata=False)

#MBSP.pprint(tokenized_words)
tokens_split = tokenized_words.split()
for words in tokens_split:
	for word in words:
		print '{} {}'.format(word[0].encode('ascii', 'ignore'), word[1])
