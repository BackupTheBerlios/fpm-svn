<?xml version="1.0" encoding="iso-8859-1"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:dc="http://purl.org/dc/elements/1.1/"
    xmlns:wfw="http://wellformedweb.org/CommentAPI/">

    <xsl:output method="html"/>

    <xsl:template match="/">
        <html>
            <head>
                <title><xsl:value-of select="rss/channel/title"/></title>
                <link rel="stylesheet" type="text/css" href="default.css"/>
                <script language="javascript" src="xsl_mop-up.js"/>
            </head>
            <body onload="go_decoding();">
                <div id="cometestme" style="display:none;">
                    <xsl:text disable-output-escaping="yes" >&amp;amp;</xsl:text>
                </div>
                <a name="0"/>
                <div class="heading">
                    <div class="headingdescription">
                        <xsl:value-of select="rss/channel/description"/>
                    </div>
                    <div class="headingtitle">
                        <b>
                            <a href="{rss/channel/link}">
                                <xsl:value-of select="rss/channel/title"/>
                        </a>
                    </b>
                    </div>
                </div>
                <xsl:for-each select="rss/channel/item">
                    <div class="item">
                        <a name="{position()}"/>
                        <xsl:variable name="storylink" select="link"/>
                        <a name="{substring($storylink,2)}"/>
                        <div class="itemtitle">
                            <a href="{link}">
                                <b><xsl:value-of select="title"/></b>
                            </a>
                        </div>
                        <table class="itemauthordate">
                            <tr>
                                <td>
                        <div class="itemauthor">
                            by
                            <xsl:value-of select="author"/>
                            <xsl:value-of select="dc:creator"/>
                        </div>
                                </td>
                                <td>
                        <div class="itemdate">
                            <xsl:value-of select="pubDate"/>
                        </div>
                                </td>
                            </tr>
                        </table>
                        <div class="itemdescription" name="decodeable">
                            <xsl:value-of select="description" disable-output-escaping="yes"/>
                        </div>
                        <div class="linkbar">
                            <a href="#0">top</a>
                            <a href="{link}">
                                | full story
                            </a>
                            <a href="mailto:ivop@free.fr">
                                | e-mail
                            </a>
                        </div>
                    </div>
                </xsl:for-each>
                <div class="toc">
                    <p>
                        <a href="test.xml">
                            <img src="feed.png" alt="[feed]"/>
                            RSS Feed
                        </a>
                    </p>
                    <b> contents </b>
                    <p/>
                    <ul>
                        <xsl:for-each select="rss/channel/item">
                            <li>
                                <a href="{link}">
                                    <b><xsl:value-of select="title"/></b>
                                </a>
                            </li>
                        </xsl:for-each>
                    </ul>
                </div>
                <div class="logo">
                    <img src="01101011.png"/>
                </div>
            </body>
        </html>
    </xsl:template>
</xsl:stylesheet>
