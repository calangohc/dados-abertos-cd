<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:template match="/">
    <html>
	  <head>
        <title>Deputados</title>
      </head>
	  <body>
         <h1>Deputados</h1>
		 <table>
           <xsl:for-each select="deputados/deputado">
             <tr>
		       <td><xsl:value-of select="nomeParlamentar"/></td>
			   <td><xsl:value-of select="partido"/></td>
			   <td><xsl:value-of select="sexo"/></td>
             </tr> 
           </xsl:for-each>
		 </table>
      </body>
	</html>
   </xsl:template>
</xsl:stylesheet>
