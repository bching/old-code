import MBSP

inpt = ""

with open('_raw/raw-split-v6c.txt', 'r') as f:
	inpt = f.read().replace('\n', ' ')

ustr = unicode(inpt,encoding="utf-8")

tokenized_sentences = MBSP.tokenizer.split(ustr, tags=False, replace={}, ignore=[])

for sent in tokenized_sentences:
	print sent.encode('ascii', 'ignore')
