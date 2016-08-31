#include <vector>
#include <algorithm>

#include "numbermatcher.h"
#include "theme.h"
#include "syntaxhighlighter.h"

//==============================================================================

const int SPACES_IN_TAB = 4;

// Text block states: 0 - 80 are used for indentation value.
// Larger values are special cases.

enum class BlockState : int
{
	LongStringSingleStart = 81,
	LongStringSingleMiddle,
	LongStringDoubleStart,
	LongStringDoubleMiddle
};

enum class TokenType
{
	Undecided,
	Keyword,
	Operator,
	String,
	Number,
	Comment,
	VSCore,
	VSNamespace,
	VSFunction,
};

struct Token
{
	QString text;
	int start;
	int length;
	TokenType type;

	Token(const QString & a_text, int a_start, int a_length, TokenType a_type):
		text(a_text), start(a_start), length(a_length), type(a_type){}
};

//==============================================================================

SyntaxHighlighter::SyntaxHighlighter(QTextDocument * a_pDocument) : QSyntaxHighlighter(a_pDocument)
{
	slotLoadSettings();
	m_coreName = "core";

	m_keywordsList << "False" << "None" << "True" << "and" << "as" <<
		"assert" << "break" << "class" << "continue" << "def" << "del" <<
		"elif" << "else" << "except" << "finally" << "for" << "from" <<
		"global" << "if" << "import" << "in" << "is" << "lambda" <<
		"nonlocal" << "not" << "or" << "pass" << "raise" << "return" <<
		"try" << "while" << "with" << "yield";

	// MUST be sorted by length in descending order.
	m_operatorsList << "//=" << ">>=" << "<<=" << "**=" << "**" << "//" <<
		"<<" << ">>" << "<=" << ">=" << "==" << "!=" << "->" << "+=" << "-=" <<
		"*=" << "/=" << "%=" << "&=" << "|=" << "^=" << "+" << "-" << "*" <<
		"/" << "%" << "&" << "|" << "^" << "~" << "<" << ">" << "(" << ")" <<
		"[" << "]" << "{" << "}" << "," << ":" << "." << ";" << "@" << "=";
	// Don't trust yourself. Sort it.
	std::sort(m_operatorsList.begin(), m_operatorsList.end(),
		[&](const QString & a_first, const QString & a_second)->bool
		{
			return (a_first.length() > a_second.length());
		});
}

// END OF SyntaxHighlighter::SyntaxHighlighter(QTextDocument * a_pDocument,
//		VSPluginsList a_pluginsList)
//==============================================================================

SyntaxHighlighter::~SyntaxHighlighter()
{

}


QTextCharFormat SyntaxHighlighter::getDefaultTextFormat(
	const QString & a_textFormatID)
{
	// Standard "Icecream" theme

	QTextCharFormat defaultFormat;

	if (a_textFormatID == TEXT_FORMAT_ID_COMMON_SCRIPT_TEXT)
	{
		QFont commonScriptFont = defaultFormat.font();
		commonScriptFont.setFamily("monospace");
		commonScriptFont.setStyleHint(QFont::Monospace);
		commonScriptFont.setFixedPitch(true);
		commonScriptFont.setKerning(false);
		commonScriptFont.setPointSize(10);
		defaultFormat.setFont(commonScriptFont);

		return defaultFormat;
	}
	else if (a_textFormatID == TEXT_FORMAT_ID_KEYWORD)
	{
		defaultFormat.setForeground(QColor("#0EAA95"));
		defaultFormat.setFontWeight(QFont::Bold);
	}
	else if (a_textFormatID == TEXT_FORMAT_ID_OPERATOR)
	{
		defaultFormat.setForeground(QColor("#b9672a"));
	}
	else if (a_textFormatID == TEXT_FORMAT_ID_STRING)
	{
		defaultFormat.setForeground(QColor("#a500bc"));
	}
	else if (a_textFormatID == TEXT_FORMAT_ID_NUMBER)
	{
		defaultFormat.setForeground(QColor("#3f8300"));
	}
	else if (a_textFormatID == TEXT_FORMAT_ID_COMMENT)
	{
		defaultFormat.setForeground(QColor("#808080"));
	}
	else if (a_textFormatID == TEXT_FORMAT_ID_VS_CORE)
	{
		defaultFormat.setForeground(QColor("#0673E0"));
		defaultFormat.setFontWeight(QFont::Bold);
	}
	else if (a_textFormatID == TEXT_FORMAT_ID_VS_NAMESPACE)
	{
		defaultFormat.setForeground(QColor("#0673E0"));
		defaultFormat.setFontWeight(QFont::Bold);
	}
	else if (a_textFormatID == TEXT_FORMAT_ID_VS_FUNCTION)
	{
		defaultFormat.setForeground(QColor("#0673E0"));
		defaultFormat.setFontWeight(QFont::Bold);
	}
	else if (a_textFormatID == TEXT_FORMAT_ID_VS_ARGUMENT)
	{
		defaultFormat.setForeground(QColor("#a500bc"));
	}

	return defaultFormat;
}

void SyntaxHighlighter::slotLoadSettings()
{
	m_keywordFormat = getDefaultTextFormat(
		TEXT_FORMAT_ID_KEYWORD);
	m_operatorFormat = getDefaultTextFormat(
		TEXT_FORMAT_ID_OPERATOR);
	m_stringFormat = getDefaultTextFormat(
		TEXT_FORMAT_ID_STRING);
	m_numberFormat = getDefaultTextFormat(
		TEXT_FORMAT_ID_NUMBER);
	m_commentFormat = getDefaultTextFormat(
		TEXT_FORMAT_ID_COMMENT);
	m_vsCoreFormat = getDefaultTextFormat(
		TEXT_FORMAT_ID_VS_CORE);
	m_vsNamespaceFormat = getDefaultTextFormat(
		TEXT_FORMAT_ID_VS_NAMESPACE);
	m_vsFunctionFormat = getDefaultTextFormat(
		TEXT_FORMAT_ID_VS_FUNCTION);
	m_vsArgumentFormat = getDefaultTextFormat(
		TEXT_FORMAT_ID_VS_ARGUMENT);
}


void SyntaxHighlighter::highlightBlock(const QString & a_text)
{
	setCurrentBlockState(0);
	std::vector<Token> tokens;

	int i = 0;
	int j = 0;
	int textLength = a_text.length();
	bool goToNextToken = false;

	while(i < textLength)
	{
//------Long string continuation, single quotes---------------------------------

		if((i == 0) && (
			(previousBlockState() == (int)BlockState::LongStringSingleStart) ||
			(previousBlockState() == (int)BlockState::LongStringSingleMiddle)))
		{
			bool foundMatchingQuotes = false;
			for(j = i; j < textLength - 2; ++j)
			{
				if((a_text.mid(j, 3) == "'''") &&
					((j == 0) || ((j != 0) && (a_text[j - 1] != '\\'))))
				{
					foundMatchingQuotes = true;
					break;
				}
			}

			if(foundMatchingQuotes)
			{
				j += 3;
				Token newToken(a_text.mid(i, j-i), i, j, TokenType::String);
				tokens.push_back(newToken);
				i = j;
				continue;
			}
			else
			{
				setCurrentBlockState((int)BlockState::LongStringSingleMiddle);
				setFormat(0, a_text.length(), m_stringFormat);
				return;
			}
		}

//------Long string continuation, double quotes---------------------------------

		if((i == 0) && (
			(previousBlockState() == (int)BlockState::LongStringDoubleStart) ||
			(previousBlockState() == (int)BlockState::LongStringDoubleMiddle)))
		{
			bool foundMatchingQuotes = false;
			for(j = i; j < textLength - 2; ++j)
			{
				if((a_text.mid(j, 3) == "\"\"\"") &&
					((j == 0) || ((j != 0) && (a_text[j - 1] != '\\'))))
				{
					foundMatchingQuotes = true;
					break;
				}
			}

			if(foundMatchingQuotes)
			{
				j += 3;
				Token newToken(a_text.mid(i, j-i), i, j - i, TokenType::String);
				tokens.push_back(newToken);
				i = j;
				continue;
			}
			else
			{
				setCurrentBlockState((int)BlockState::LongStringDoubleMiddle);
				setFormat(0, a_text.length(), m_stringFormat);
				return;
			}
		}

//------Long string, single quotes.---------------------------------------------

		if((((a_text[i].toLower() == 'r') || (a_text[i].toLower() == 'u')) &&
			(a_text.mid(i + 1, 3) == "'''")) || (a_text.mid(i, 3) == "'''"))
		{
			if(a_text[i] == '\'')
				j = i + 3;
			else
				j = i + 4;

			bool foundMatchingQuotes = false;
			for(; j < textLength - 2; ++j)
			{
				if((a_text.mid(j, 3) == "'''") &&
					((j == 0) || ((j != 0) && (a_text[j - 1] != '\\'))))
				{
					foundMatchingQuotes = true;
					break;
				}
			}

			if(foundMatchingQuotes)
			{
				j += 3 - i;
				Token newToken(a_text.mid(i, j), i, j, TokenType::String);
				tokens.push_back(newToken);
				i += j;
				continue;
			}
			else
			{
				j = textLength - i;
				Token newToken(a_text.mid(i, j), i, j, TokenType::String);
				tokens.push_back(newToken);
				setCurrentBlockState((int)BlockState::LongStringSingleStart);
				break;
			}
		}

//------Long string, double quotes----------------------------------------------

		if((((a_text[i].toLower() == 'r') || (a_text[i].toLower() == 'u')) &&
			(a_text.mid(i + 1, 3) == "\"\"\"")) ||
			(a_text.mid(i, 3) == "\"\"\""))
		{
			if(a_text[i] == '\"')
				j = i + 3;
			else
				j = i + 4;

			bool foundMatchingQuotes = false;
			for(; j < textLength - 2; ++j)
			{
				if((a_text.mid(j, 3) == "\"\"\"") &&
					((j == 0) || ((j != 0) && (a_text[j - 1] != '\\'))))
				{
					foundMatchingQuotes = true;
					break;
				}
			}

			if(foundMatchingQuotes)
			{
				j += 3 - i;
				Token newToken(a_text.mid(i, j), i, j, TokenType::String);
				tokens.push_back(newToken);
				i += j;
				continue;
			}
			else
			{
				j = textLength - i;
				Token newToken(a_text.mid(i, j), i, j, TokenType::String);
				tokens.push_back(newToken);
				setCurrentBlockState((int)BlockState::LongStringDoubleStart);
				break;
			}
		}

//------Short string, single quotes---------------------------------------------

		if((a_text[i] == '\'') || (a_text.mid(i, 2).toLower() == "r'") ||
			(a_text.mid(i, 2).toLower() == "u'"))
		{
			if(a_text[i] == '\'')
				j = i + 1;
			else
				j = i + 2;

			for(; j < textLength; ++j)
			{
				if((a_text[j] == '\'') &&
					((j == 0) || ((j != 0) && (a_text[j - 1] != '\\'))))
					break;
			}

			j += 1 - i;
			Token newToken(a_text.mid(i, j), i, j, TokenType::String);
			tokens.push_back(newToken);
			i += j;
			continue;
		}

//------Short string, double quotes---------------------------------------------

		if((a_text[i] == '\"') || (a_text.mid(i, 2).toLower() == "r\"") ||
			(a_text.mid(i, 2).toLower() == "u\""))
		{
			if(a_text[i] == '\"')
				j = i + 1;
			else
				j = i + 2;

			for(; j < textLength; ++j)
			{
				if((a_text[j] == '\"') &&
					((j == 0) || ((j != 0) && (a_text[j - 1] != '\\'))))
					break;
			}

			j += 1 - i;
			Token newToken(a_text.mid(i, j), i, j, TokenType::String);
			tokens.push_back(newToken);
			i += j;
			continue;
		}

//------Comment-----------------------------------------------------------------

		if(a_text[i] == '#')
		{
			j = a_text.length();
			Token newToken(a_text.mid(i, j-i), i, j, TokenType::Comment);
			tokens.push_back(newToken);
			break;
		}

//------Keyword or unknown word-------------------------------------------------

		if((a_text[i].isLetter()) || (a_text[i] == '_'))
		{
			for(j = i; j < textLength; ++j)
			{
				if(!(a_text[j].isLetterOrNumber() || (a_text[j] == '_')))
					break;
			}

			j = j - i;
			QString word = a_text.mid(i, j);
			Token newToken(word, i, j , TokenType::Undecided);
			for(const QString & keyword : m_keywordsList)
			{
				if(word == keyword)
				{
					newToken.type = TokenType::Keyword;
					break;
				}
			}
			tokens.push_back(newToken);
			i += j;
			continue;
		}

//------Number------------------------------------------------------------------

		NumberMatcher matcher;
		if(matcher.beginsWithNumber(a_text, i))
		{
			j = matcher.matchedLength();
			Token newToken(a_text.mid(i, j), i, j, TokenType::Number);
			tokens.push_back(newToken);
			i += j;
			continue;
		}

//------Operator----------------------------------------------------------------

		goToNextToken = false;
		for(const QString & operatorString : m_operatorsList)
		{
			if(goToNextToken)
				break;

			j = operatorString.length();
			QString substring = a_text.mid(i, j);
			if(substring == operatorString)
			{
				Token newToken(substring, i, j, TokenType::Operator);
				tokens.push_back(newToken);
				i += j;
				goToNextToken = true;
			}
		}
		if(goToNextToken)
			continue;

//------------------------------------------------------------------------------

		i++;
	}

	size_t tokensNumber = tokens.size();

	if(tokensNumber == 0)
		setCurrentBlockState(previousBlockState());

	for(size_t k = 0; k < tokensNumber; ++k)
	{
		Token & token = tokens[k];

		if(token.text == m_coreName)
			token.type = TokenType::VSCore;
		else if((k > 1) && (tokens[k - 1].text == ".") &&
			(tokens[k - 2].type == TokenType::VSCore))
		{
			token.type = TokenType::VSNamespace;
		}
		else if((k > 3) && (tokens[k - 1].text == ".") &&
			(tokens[k - 2].type == TokenType::VSNamespace) &&
			(tokens[k - 3].text == ".") &&
			(tokens[k - 4].type == TokenType::VSCore))
		{
			token.type = TokenType::VSFunction;
		}

		if(token.type == TokenType::Keyword)
			setFormat(token.start, token.length, m_keywordFormat);
		else if(token.type == TokenType::Operator)
			setFormat(token.start, token.length, m_operatorFormat);
		else if(token.type == TokenType::String)
			setFormat(token.start, token.length, m_stringFormat);
		else if(token.type == TokenType::Number)
			setFormat(token.start, token.length, m_numberFormat);
		else if(token.type == TokenType::Comment)
			setFormat(token.start, token.length, m_commentFormat);
		else if(token.type == TokenType::VSCore)
			setFormat(token.start, token.length, m_vsCoreFormat);
		else if(token.type == TokenType::VSNamespace)
			setFormat(token.start, token.length, m_vsNamespaceFormat);
		else if(token.type == TokenType::VSFunction)
			setFormat(token.start, token.length, m_vsFunctionFormat);

	}
}

// END OF void SyntaxHighlighter::highlightBlock(const QString & a_text)
//==============================================================================
