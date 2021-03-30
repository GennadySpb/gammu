/* Test for decoding SMS on Nokia 6510 driver */

#include <gammu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

#include "../libgammu/protocol/protocol.h"	/* Needed for GSM_Protocol_Message */
#include "../libgammu/gsmstate.h"	/* Needed for state machine internals */

#include "../helper/message-display.h"

unsigned char data[] = {
	0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x54, 0x00, 0x00, 0x01, 0xE6, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B,
	0x00, 0x33, 0x00, 0x32, 0x00, 0x34, 0x00, 0x38, 0x00, 0x34, 0x00, 0x30, 0x00, 0x35, 0x00, 0x33,
	0x00, 0x30, 0x00, 0x38, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x11, 0x00, 0x14, 0x91, 0x53, 0x58, 0x76, 0x98, 0x21, 0x43, 0x65, 0x87, 0x19, 0x32, 0x00, 0x00,
	0xFF, 0x4B, 0x41, 0x36, 0xFB, 0x2D, 0x0F, 0xB3, 0x40, 0xE3, 0x34, 0x68, 0x9E, 0x2E, 0xD3, 0xCB,
	0xBF, 0x10, 0xC8, 0x5A, 0x26, 0xA7, 0xC3, 0xED, 0xF7, 0x38, 0x1D, 0x02, 0x11, 0xDF, 0xED, 0xB0,
	0x3B, 0xFD, 0x03, 0x25, 0xDF, 0xA0, 0x78, 0xBD, 0x3C, 0xA7, 0xBF, 0x41, 0xF7, 0x72, 0x79, 0x0D,
	0x2A, 0xBB, 0xC9, 0x20, 0x73, 0xFD, 0x2D, 0x4F, 0x83, 0xC4, 0x78, 0xB6, 0x0B, 0x14, 0x04, 0xC1,
	0xD9, 0xF5, 0x79, 0x08, 0x01, 0x00, 0xDF, 0x01, 0x00, 0x01, 0x01, 0x03, 0x00, 0x98, 0x00, 0x41,
	0x00, 0x6C, 0x00, 0x6C, 0x00, 0x6F, 0x00, 0x72, 0x00, 0x61, 0x00, 0x2C, 0x00, 0x20, 0x00, 0x63,
	0x00, 0x69, 0x00, 0x20, 0x00, 0x73, 0x00, 0x69, 0x00, 0x65, 0x00, 0x74, 0x00, 0x65, 0x00, 0x3F,
	0x00, 0x21, 0x00, 0x20, 0x00, 0x56, 0x00, 0x65, 0x00, 0x64, 0x00, 0x69, 0x00, 0x61, 0x00, 0x6D,
	0x00, 0x6F, 0x00, 0x63, 0x00, 0x69, 0x00, 0x21, 0x00, 0x20, 0x00, 0x44, 0x00, 0x6F, 0x00, 0x6D,
	0x00, 0x61, 0x00, 0x6E, 0x00, 0x69, 0x00, 0x3F, 0x00, 0x20, 0x00, 0x49, 0x00, 0x6F, 0x00, 0x20,
	0x00, 0x71, 0x00, 0x75, 0x00, 0x65, 0x00, 0x73, 0x00, 0x74, 0x00, 0x6F, 0x00, 0x20, 0x00, 0x77,
	0x00, 0x65, 0x00, 0x65, 0x00, 0x6B, 0x00, 0x20, 0x00, 0x65, 0x00, 0x6E, 0x00, 0x64, 0x00, 0x20,
	0x00, 0x66, 0x00, 0x75, 0x00, 0x6F, 0x00, 0x72, 0x00, 0x69, 0x00, 0x20, 0x00, 0x62, 0x00, 0x78,
	0x00, 0x6C, 0x00, 0x2E, 0x00, 0x20, 0x00, 0x41, 0x00, 0x20, 0x00, 0x70, 0x00, 0x6C, 0x00, 0x75,
	0x00, 0x73, 0x00, 0x21, 0x00, 0x00, 0x04, 0x00, 0x1A, 0x00, 0x2B, 0x00, 0x33, 0x00, 0x32, 0x00,
	0x34, 0x00, 0x38, 0x00, 0x34, 0x00, 0x30, 0x00, 0x35, 0x00, 0x33, 0x00, 0x30, 0x00, 0x38, 0x00,
	0x38, 0x00, 0x00, 0x0C, 0x00, 0x02, 0x31, 0x00, 0x07, 0x00, 0x01, 0x0E, 0x05, 0x00, 0x01, 0x02,
	0x06, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x01, 0x00, 0x0B, 0x00, 0x01, 0x00, 0x09,
	0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00
};

const char text[] = "Allora, ci siete?! Vediamoci! Domani? Io questo week end fuori bxl. A plus!";
char decoded_text[200];

/* This is not part of API! */
extern GSM_Error N6510_DecodeFilesystemSMS(GSM_StateMachine * s, GSM_MultiSMSMessage * sms, GSM_File * FFF, int location);

int main(int argc UNUSED, char **argv UNUSED)
{
	GSM_Debug_Info *debug_info;
	GSM_StateMachine *s;
	GSM_File file;
	GSM_Error error;
	GSM_MultiSMSMessage sms;

	/* Init locales for proper output */
	GSM_InitLocales(NULL);

	debug_info = GSM_GetGlobalDebug();
	GSM_SetDebugFileDescriptor(stderr, FALSE, debug_info);
	GSM_SetDebugLevel("textall", debug_info);

	/* Allocates state machine */
	s = GSM_AllocStateMachine();
	test_result(s != NULL);

	debug_info = GSM_GetDebug(s);
	GSM_SetDebugGlobal(TRUE, debug_info);

	/* Init file */
	file.Buffer = malloc(sizeof(data));
	memcpy(file.Buffer, data, sizeof(data));
	file.Used = sizeof(data);
	file.ID_FullName[0] = 0;
	file.ID_FullName[1] = 0;
	GSM_GetCurrentDateTime(&(file.Modified));

	/* Parse it */
	error = N6510_DecodeFilesystemSMS(s, &sms, &file, 0);

	/* Display message */
	DisplayMultiSMSInfo(&sms, FALSE, TRUE, NULL, NULL);
	DisplayMultiSMSInfo(&sms, TRUE, TRUE, NULL, NULL);

	/* Free state machine */
	GSM_FreeStateMachine(s);

	/* Check expected text */
	/* We do not compare full text due to locales problem */
	EncodeUTF8(decoded_text, sms.SMS[0].Text);
	test_result(strcmp(text, decoded_text) == 0);

	gammu_test_result(error, "N6510_DecodeFilesystemSMS");

	return 0;
}

/* Editor configuration
 * vim: noexpandtab sw=8 ts=8 sts=8 tw=72:
 */
