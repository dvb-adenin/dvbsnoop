/*

 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de (rasc)


Revision 0.1 20151104 adenin
 -SES Astra LCN2

*/


#include "dvbsnoop.h"
#include "dvb_descriptor_ses_astra.h"
#include "strings/dvb_str.h"
#include "misc/hexprint.h"
#include "misc/output.h"

/*
 *
 * Private DVB descriptors
 * User Space: SES ASTRA
 *
 */

//
void descriptor_PRIVATE_SES_ASTRA_0x88 (u_char *b)
{
	int  tag, len;
	u_char     ISO639_language_code[4];

	tag		 = b[0];
	len       	 = b[1];
	
	out_nl (4,"--> list name descriptor ");

	getISO639_3 (ISO639_language_code, b+2);
	out_nl (4,"  ISO639_language_code:  %3.3s", ISO639_language_code);
	print_text_468A (4, "Text: ", b+5, len-3);
}

//service id
void descriptor_PRIVATE_SES_ASTRA_0xd1 (u_char *b)
{
	int  tag, len;
	tag	 = b[0];
	len	 = b[1];

	outBit_Sx_NL (3,"  service_ID: ", b+2, 0,16);
}
