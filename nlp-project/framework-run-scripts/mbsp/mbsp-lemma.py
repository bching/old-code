import MBSP

inpt = ""

with open('_raw/lemmaCase-v6.txt', 'r') as f:
#	inS = f.read()
#	parsed_string = MBSP.parse(inS)
#	text = MBSP.Text(parsed_string, token=[WORD, POS, CHUNK, PNP, REL, ANCHOR, LEMMA])
#	print text.sentences

	for line in f:
		inpt = line
		print inpt
		ustr= unicode(inpt,encoding="utf-8")
		tokenized_lemmas = MBSP.lemmatize(ustr, tokenize=True)
		print tokenized_lemmas
		#for lem in tokenized_lemmas:
			#print lem
		#sentence = MBSP.tokenize(ustr);
		#print tokenized_lemmas
			#pos_word = MBSP.tag(word, tokenize=False, lemmata=False)
			#print MBSP.lemma(word.encode('ascii', 'ignore'))
			#print '{} {}'.format(word[0].encode('ascii', 'ignore'), word[1])



