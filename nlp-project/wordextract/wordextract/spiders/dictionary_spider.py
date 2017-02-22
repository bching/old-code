import scrapy

from wordextract.items import DictionaryItem
## use wordextract to load up list of words to iterate-search
import get_words 

class DictionarySpider(scrapy.Spider):
	name = "dictionary_spider"
	allowed_domains = "ahdictionary.com"
	n = get_words.ExtractWords()
	query = n.words()
	#start_urls = ["http://dictionary.reference.com/browse/" + query[0]] 
	#base_url_0 = 'http://thefreedictionary.com/'
	base_url = 'http://www.ahdictionary.com/word/search.html?q='
	start_urls = []
	i = 0

	for term in query:
		url = base_url + term.strip()
		start_urls.append(url)

	def make_requets_from_url(self, url):
		return Request(url, dont_filter=True, meta = {
			'dont_redirect': True,
			'handle_httpstatus_list': [301,302]
			})

	def parse(self, response):
		item = DictionaryItem()

#### xpath_0 - xpath_1 are for dictionary.reference.com
#### xpath_2 is for thefreedictionary.com

#		xpath_0 = "//div/span[@data-syllable]/text()"
#		xpath_1 = "//div[@class='def-content']/a[@class='dbox-xref dbox-roman']/text()" 
		xpath_2 = "//div[@class='pseg']/b/."
		#item['word_0'] = response.selector.xpath('//div/span[@data-syllable]/text()').extract()
		#item['word_1'] = response.selector.xpath('//div[@class="def-content"]/a[@class="dbox-xref dbox-roman"]/text()[contains(.,%str(start_urls[i]))]').extract()
		item['word_0'] = response.selector.xpath(xpath_2).extract()
		#item['word_1'] = response.selector.xpath(xpath_1).extract()
		yield item


##### xpath code to match response #####
#			response.selector.xpath('//div[@class="def-content"]/a[@class="dbox-xref"]/text()')
#			response.selector.xpath('//div/span[@data-syllable]/text()')
#			response.selector.xpath('//div[@class="def-content"]/a[@class="dbox-xref dbox-roman"]/text()[contains(.,'play')]')

#			response.selector.xpath('//div[@class="pseg"]/b/text()')	













