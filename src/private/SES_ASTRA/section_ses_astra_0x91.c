/*

 DVBSNOOP

 a dvb sniffer  and mpeg2 stream analyzer tool
 http://dvbsnoop.sourceforge.net/

 (c) 2001-2006   Rainer.Scherg@gmx.de  (rasc)


  -- User defined table // Private

Revision 0.1 20151104 adenin
 -SES Astra LCN2

*/




#include "dvbsnoop.h"
#include "section_ses_astra_0x91.h"
#include "descriptors/descriptor.h"
#include "strings/dvb_str.h"
#include "misc/output.h"
#include "misc/hexprint.h"



void section_PRIVATE_SES_ASTRA_0x91 (u_char *b, int len)
{
	u_int	table_id;
	u_int	tag;
	u_int	section_length;
	u_int	lcn_start;
	u_int	x;

	out_nl (3,"User_Defined-decoding....");
	table_id = outBit_S2Tx_NL (3,"Table_ID: ",	b, 0, 8,
		"SES_ASTRA Logical Channel Numbers (LCN) Table");
	if (table_id != 0x91)
	{
		out_nl (3,"wrong Table ID");
		return;
	}


	outBit_Sx_NL (3,"Section_syntax_indicator: ",	b, 8, 1);	// ==1 
	outBit_Sx_NL (3,"private_indicator: ",		b, 9, 1);
	outBit_Sx_NL (6,"reserved: ",			b,10, 2);
	section_length =
	outBit_Sx_NL (5,"private_section_length: ",	b,12,12);

	outBit_Sx_NL (3,"table_id_extension: ",		b, 24,16);
	outBit_Sx_NL (6,"reserved: ",			b, 40, 2);
	outBit_Sx_NL (3,"Version_number: ",		b, 42, 5);
	outBit_S2x_NL(3,"Current_next_indicator: ",	b, 47, 1,
			(char *(*)(u_long))dvbstrCurrentNextIndicator );
	outBit_Sx_NL (3,"Section_number: ",		b, 48, 8);
	outBit_Sx_NL (3,"Last_section_number: ",	b, 56, 8);

	b += 8;
	section_length -= 5;

	out_NL (3);
	outBit_Sx_NL (3,"SYNC(?): ",			b, 0, 24);
	outBit_Sx_NL (3,"unknown data bit: ",		b, 24, 1);
	lcn_start = outBit_Sx_NL (3,"Startbit: ",	b, 25, 1);
	outBit_Sx_NL (3,"unknown data: ",		b, 26, 6);
	outBit_Sx_NL (3,"unknown data: ",		b, 32, 8);
	outBit_Sx_NL (3,"unknown data: ",		b, 40, 8);

	if(lcn_start)
	{
		outBit_Sx_NL (3,"unknown data: ",	b, 48, 8);
		outBit_Sx_NL (3,"unknown data: ",	b, 56, 8);
		outBit_Sx_NL (3,"unknown data: ",	b, 64, 8);
		outBit_Sx_NL (3,"unknown data: ",	b, 72, 8);
		b += 10;
		section_length -= 10;

		x = descriptor (b, DVB_SI);
		b    += x;
		section_length -= x;

		x = descriptor (b, DVB_SI);
		b    += x;
		section_length -= x;

		x = descriptor (b, DVB_SI);
		b    += x;
		section_length -= x;

		outBit_Sx_NL (3,"unknown data: ",	b, 0, 16);
		b += 2;
		section_length -=2;
	}
	else
	{
		b += 6;
		section_length -= 6;
	}

	while(section_length > 4)
	{
		outBit_Sx_NL (3,"service_ID: ",			b,  0,16);
		outBit_Sx_NL (3,"transport_stream_ID: ",	b, 16,16);
		outBit_Sx_NL (3,"Original_network_id: ",	b, 32,16);
		outBit_Sx_NL (3,"(?): ",			b, 48,16);
		outBit_Sx_NL (3,"(?): ",			b, 64,16);
		outBit_Sx_NL (3,"(?): ",			b, 80,16);
		b += 12;
		section_length -=12;

		x = descriptor (b, DVB_SI);
		b += x;
		section_length -= x;

		do
		{
			tag = b[0];
			x = descriptor (b, DVB_SI);
			b += x;
			section_length -= x;
		}while (b[0]!= 0xd1);
	}
   outBit_Sx_NL (5,"CRC: ",		b, 0, 32);

}




