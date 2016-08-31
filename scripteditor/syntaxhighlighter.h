#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QStringList>


class SyntaxHighlighter : public QSyntaxHighlighter
{
	Q_OBJECT

	public:

		SyntaxHighlighter(QTextDocument * a_pDocument);
		virtual ~SyntaxHighlighter();

	protected:

		void highlightBlock(const QString & a_text) Q_DECL_OVERRIDE;

	private:
		QTextCharFormat SyntaxHighlighter::getDefaultTextFormat(
			const QString & a_textFormatID);

		void slotLoadSettings();

		QString m_coreName;

		QStringList m_keywordsList;
		QStringList m_operatorsList;

		QTextCharFormat m_keywordFormat;
		QTextCharFormat m_operatorFormat;
		QTextCharFormat m_stringFormat;
		QTextCharFormat m_numberFormat;
		QTextCharFormat m_commentFormat;
		QTextCharFormat m_vsCoreFormat;
		QTextCharFormat m_vsNamespaceFormat;
		QTextCharFormat m_vsFunctionFormat;
		QTextCharFormat m_vsArgumentFormat;
};

#endif // SYNTAXHIGHLIGHTER_H
