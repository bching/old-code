import os
from spacy.en import English

#INSTANTIATE SPACY PARSER
nlp = English()

strIn = ""
tokenCount = 0
sents = []

#TO REMOVE LINE BREAKS
with open('/Users/stc1563/programming/research/test-cases/_raw/raw-split-v6c.txt', 'r') as f:
	strIn=f.read().replace('\n', ' ')

#TO KEEP LINE BREAKS
#with open('/Users/stc1563/programming/research/test-cases/_raw/lemmaCase-v6.txt', 'r') as f:
#	strIn=f.read();
#	for line in f:
#		tokenSents = nlp(unicode(line,encoding="utf-8"))
#		for span in tokenSents.sents:
#			sent = ''.join(tokenSents[i].string for i in range(span.start, span.end)).strip()
#			sents.append(sent)

#spacy parser creates tokens objects with callable methods that return nlp component results
tokens = nlp(unicode(strIn,encoding="utf-8"))

#sents property returns spans
#spans have indices into original string
#where each index value returns a token
#SENTENCE SPLITTING
#for span in tokens.sents:
#	#go from the start to the end of the span, returning each token in the sentence
#	#combine each token using join()
#	sent = ''.join(tokens[i].string for i in range(span.start, span.end)).strip()
#	sents.append(sent)
#for sentence in sents:
#	tokenCount+=1
#	print '{}'.format(sentence.encode('ascii', 'ignore'))
#END SENTENCE SPLITTING

for span in tokens.sents:
	#sent = tokens[i] for i in range(span.start, span.end).strip()
	sent = [tokens[i] for i in range(span.start, span.end)]
	for token in sent:
		tokenCount += 1

		#PRINT LEMMA AND POS
		print '{} {} {}'.format(token.orth_.encode('ascii', 'ignore'), token.lemma_.encode('ascii', 'ignore'), token.pos_)
		
		#PRINT ONLY POS
		#print '{} {}'.format(token.orth_.encode('ascii', 'ignore'), token.pos_)

		#PRINT NER ENTITY 
		#print tokenCount, ''.join(token.orth_.encode('ascii', 'ignore')), token.ent_type_ if token.ent_type_ != "" else "_"


