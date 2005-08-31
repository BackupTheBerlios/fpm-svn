<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version="1.0">

  <xsl:output method="html" indent="no"/>
 
  <xsl:param name="toc.section.depth" select="'4'"/>

  <xsl:param name="html.stylesheet" select="'default.css'"/>
  <xsl:param name="html.stylesheet.type" select="'text/css'"/>

  <xsl:param name="html.cleanup" select="'1'"/>
  <xsl:param name="make.valid.html" select="'1'"/>
  <xsl:param name="make.single.year.ranges" select="'1'"/>
  <xsl:param name="make.year.ranges" select="'1'"/>

  <!-- Use ID value for generated filenames -->
  <xsl:param name="use.id.as.filename" select="'1'"/>

  <xsl:param name="admon.graphics" select="'0'"/>
  <xsl:param name="navig.graphics" select="'0'"/>
  <xsl:param name="navig.showtitles" select="'0'"/>

  <!-- Label sections too (eg. 2.1, 2.1.1) -->
  <xsl:param name="section.autolabel" select="'1'"/>
  <xsl:param name="section.label.includes.component.label" select="'1'"/>

  <!-- Use informal procedures; no need to number them -->
  <xsl:param name="formal.procedures" select="'0'"/>

  <xsl:template name="user.header.navigation">
      <xsl:text disable-output-escaping="no">
          <![CDATA[BEGINOFTABLEHERECHUNK]]>
      </xsl:text>
  </xsl:template>

  <xsl:template name="user.header.content">
      <xsl:text disable-output-escaping="no">
          <![CDATA[BEGINOFTABLEHERESINGLE]]>
      </xsl:text>
  </xsl:template>

  <xsl:template name="user.footer.navigation">
      <xsl:text disable-output-escaping="no">
          <![CDATA[ENDOFTABLEHERECHUNK]]>
      </xsl:text>
  </xsl:template>

  <xsl:template name="user.footer.content">
      <xsl:text disable-output-escaping="no">
          <![CDATA[ENDOFTABLEHERESINGLE]]>
      </xsl:text>
  </xsl:template>

  <xsl:template match="application">
      <b><xsl:apply-templates/></b>
  </xsl:template>

</xsl:stylesheet>
