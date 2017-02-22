class ExtractWords:

	def words(self):
		with open('dict_terms.txt') as f:
			result = []
			for line in f.readlines():
				 result.append(line)
			return result

#n = ExtractWords()
#n.get_words()


