/*
 * Copyright 2010 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software 
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors:
 *      Maros Barabas  <mbarabas@redhat.com>
 */


/* Standard header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

/* CVSS */
#include <cvss.h>

#include "oscap-tool.h"

void print_cvss_usage(const char *pname, FILE * out, char *msg)
{
	fprintf(out,
		"Usage: %s [general-options] cvss [operation|--help] metrics [--base <num>]\n"
		"\n"
		"\n"
		"Operation:\n"
		"   base\r\t\t\t\t - Calculate base score from metrics.\n"
		"   temporal \r\t\t\t\t - Calculate temporal score from metrics and base score.\n"
		"   environmental\r\t\t\t\t - Calculate environmental score from metrics.\n"
		"\n"
		"Metrics:\n"
		"   --AV=[local|adjacent-network|network]\r\t\t\t\t\t - Access Vector\n"
		"   --AC=[low|medium|high]\r\t\t\t\t - Access Complexity\n"
		"   --AU=[none|single|multiple]\r\t\t\t\t - Authentication\n"
		"   --CI=[none|partial|complete]\r\t\t\t\t - Confidentiality  Impact\n"
		"   --II=[none|partial|complete]\r\t\t\t\t - Integrity Impact\n"
		"   --AI=[none|partial|complete]\r\t\t\t\t - Availability Impact\n"
		"   --EX=[unproven|proof-of-concept|functional|high|not-defined]\r\t\t\t\t\t\t\t\t - Exploitability\n"
		"   --RL=[official-fix|temporary-fix|workaround|unavailable|not-defined]\r\t\t\t\t\t\t\t\t\t - Remediation Level\n"
		"   --RC=[unconfirmed|uncorrporated|confirmed|not-defined]\r\t\t\t\t\t\t\t\t - Report Confidence\n"
		"   --CD=[none|low|low-medium|medium-high|high|not-defined]\r\t\t\t\t\t\t\t\t - Collateral Damage Potential\n"
		"   --TD=[none|low|medium|high|not-defined]\r\t\t\t\t\t\t - Target Distribution\n"
		"   --CR=[low|medium|high|not-defined]\r\t\t\t\t\t - Confidentiality Requirement\n"
		"   --IR=[low|medium|high|not-defined]\r\t\t\t\t\t - Integrity Requirement\n"
		"   --AR=[low|medium|high|not-defined]\r\t\t\t\t\t - Availability Requirement\n"
		, pname);
	if (msg != NULL)
		fprintf(out, "\n%s\n", msg);
}

int getopt_cvss(int argc, char **argv, struct oscap_action *action)
{
	/* Usage: oscap cvss command metrics */
	if (action == NULL) {
		return -1;
	}

	action->std = OSCAP_STD_CVSS;
	action->cvss_metrics = malloc(sizeof(struct cvss_metrics));
	action->cvss_metrics->exe = EX_NOT_DEFINED;
	action->cvss_metrics->rle = RL_NOT_DEFINED;
	action->cvss_metrics->rce = RC_NOT_DEFINED;
	action->cvss_metrics->cde = CD_NOT_DEFINED;
	action->cvss_metrics->tde = TD_NOT_DEFINED;
	action->cvss_metrics->cre = CR_NOT_DEFINED;
	action->cvss_metrics->ire = IR_NOT_DEFINED;
	action->cvss_metrics->are = AR_NOT_DEFINED;

	/* Command */
	optind++;
	if (optind >= argc) {
		print_cvss_usage("oscap", stderr, "Error: Bad number of parameters !");
		return -1;
	}
	if (!strcmp(argv[optind], "base"))
		action->op = OSCAP_OP_BASE;
	else if (!strcmp(argv[optind], "temporal"))
		action->op = OSCAP_OP_TEMP;
	else if (!strcmp(argv[optind], "environmental"))
		action->op = OSCAP_OP_ENV;
	else
		optind--;	/* oscap xccdf --help */

	/* Command-options */
	struct option long_options[] = {
		{"help", 0, 0, 'h'},
		{"AV", 1, 0, 0},
		{"AC", 1, 0, 1},
		{"AU", 1, 0, 2},
		{"CI", 1, 0, 3},
		{"II", 1, 0, 4},
		{"AI", 1, 0, 5},
		{"EX", 1, 0, 6},
		{"RL", 1, 0, 7},
		{"RC", 1, 0, 8},
		{"CD", 1, 0, 9},
		{"TD", 1, 0, 10},
		{"CR", 1, 0, 11},
		{"IR", 1, 0, 12},
		{"AR", 1, 0, 13},
		{"base", 1, 0, 14},
		{0, 0, 0, 0}
	};

	int c;
	int getopt_index = 0;	/* index is not neccesary because we know the option from "val" */
	int ave=0, ace=0, aue=0, cie=0, iie=0, aie=0, base=0;
	optind++;		/* Increment global variable pointeing to argv array to get next opt */
	while ((c = getopt_long(argc, argv, "+h0:1:2:3:4:5:6:7:8:9:10:11:12:13:14:", long_options, &getopt_index)) != -1) {
		switch (c) {
		case 'h':	/* CVSS HELP */
			print_cvss_usage("oscap", stdout, NULL);
			return 0;
			break;
		case 0:
			ave++;
			if (!strcmp(optarg, "local")) action->cvss_metrics->ave = AV_LOCAL;
			else if (!strcmp(optarg, "adjacent-network")) action->cvss_metrics->ave = AV_ADJACENT_NETWORK;
			else if (!strcmp(optarg, "network")) action->cvss_metrics->ave = AV_NETWORK;
			else return -1;
			break;
		case 1:
		        ace++;
			if (!strcmp(optarg, "low")) action->cvss_metrics->ace = AC_LOW;
			else if (!strcmp(optarg, "medium")) action->cvss_metrics->ace = AC_MEDIUM;
			else if (!strcmp(optarg, "high")) action->cvss_metrics->ace = AC_HIGH;
			else return -1;
			break;
		case 2:
			aue++;
			if (!strcmp(optarg, "none")) action->cvss_metrics->aue = AU_NONE;
			else if (!strcmp(optarg, "single")) action->cvss_metrics->aue = AU_SINGLE_INSTANCE;
			else if (!strcmp(optarg, "multiple")) action->cvss_metrics->aue = AU_MULTIPLE_INSTANCE;
			else return -1;
			break;
		case 3:
			cie++;
			if (!strcmp(optarg, "none")) action->cvss_metrics->cie = CI_NONE;
			else if (!strcmp(optarg, "partial")) action->cvss_metrics->cie = CI_PARTIAL;
			else if (!strcmp(optarg, "complete")) action->cvss_metrics->cie = CI_COMPLETE;
			else return -1;
			break;
		case 4:
			iie++;
			if (!strcmp(optarg, "none")) action->cvss_metrics->iie = II_NONE;
			else if (!strcmp(optarg, "partial")) action->cvss_metrics->iie = II_PARTIAL;
			else if (!strcmp(optarg, "complete")) action->cvss_metrics->iie = II_COMPLETE;
			else return -1;
			break;
		case 5:
			aie++;
			if (!strcmp(optarg, "none")) action->cvss_metrics->aie = II_NONE;
			else if (!strcmp(optarg, "partial")) action->cvss_metrics->aie = II_PARTIAL;
			else if (!strcmp(optarg, "complete")) action->cvss_metrics->aie = II_COMPLETE;
			else return -1;
			break;
		case 6:
			if (!strcmp(optarg, "unproven")) action->cvss_metrics->exe = EX_UNPROVEN;
			else if (!strcmp(optarg, "proof-of-concept")) action->cvss_metrics->exe = EX_PROOF_OF_CONCEPT;
			else if (!strcmp(optarg, "functional")) action->cvss_metrics->exe = EX_FUNCTIONAL;
			else if (!strcmp(optarg, "high")) action->cvss_metrics->exe = EX_HIGH;
			else if (!strcmp(optarg, "not-defined")) action->cvss_metrics->exe = EX_NOT_DEFINED;
			else return -1;
			break;
		case 7:
			if (!strcmp(optarg, "official-fix")) action->cvss_metrics->rle = RL_OFFICIAL_FIX;
			else if (!strcmp(optarg, "temporary-fix")) action->cvss_metrics->rle = RL_TEMPORARY_FIX;
			else if (!strcmp(optarg, "workaround")) action->cvss_metrics->rle = RL_WORKAROUND;
			else if (!strcmp(optarg, "unavailable")) action->cvss_metrics->rle = RL_UNAVAILABLE;
			else if (!strcmp(optarg, "not-defined")) action->cvss_metrics->rle = RL_NOT_DEFINED;
			else return -1;
			break;
		case 8:
			if (!strcmp(optarg, "unconfirmed")) action->cvss_metrics->rce = RC_UNCONFIRMED;
			else if (!strcmp(optarg, "uncorrporated")) action->cvss_metrics->rce = RC_UNCORROBORATED;
			else if (!strcmp(optarg, "confirmed")) action->cvss_metrics->rce = RC_CONFIRMED;
			else if (!strcmp(optarg, "not-defined")) action->cvss_metrics->rce = RC_NOT_DEFINED;
			else return -1;
			break;
		case 9:
			if (!strcmp(optarg, "none")) action->cvss_metrics->cde = CD_NONE;
			else if (!strcmp(optarg, "low")) action->cvss_metrics->cde = CD_LOW;
			else if (!strcmp(optarg, "low-medium")) action->cvss_metrics->cde = CD_LOW_MEDIUM;
			else if (!strcmp(optarg, "medium-high")) action->cvss_metrics->cde = CD_MEDIUM_HIGH;
			else if (!strcmp(optarg, "high")) action->cvss_metrics->cde = CD_HIGH;
			else if (!strcmp(optarg, "not-defined")) action->cvss_metrics->cde = CD_NOT_DEFINED;
			else return -1;
			break;
		case 10:
			if (!strcmp(optarg, "none")) action->cvss_metrics->tde = TD_NONE;
			else if (!strcmp(optarg, "low")) action->cvss_metrics->tde = TD_LOW;
			else if (!strcmp(optarg, "medium")) action->cvss_metrics->tde = TD_MEDIUM;
			else if (!strcmp(optarg, "high")) action->cvss_metrics->tde = TD_HIGH;
			else if (!strcmp(optarg, "not-defined")) action->cvss_metrics->tde = TD_NOT_DEFINED;
			else return -1;
			break;
		case 11:
			if (!strcmp(optarg, "low")) action->cvss_metrics->cre = CR_LOW;
			else if (!strcmp(optarg, "medium")) action->cvss_metrics->cre = CR_MEDIUM;
			else if (!strcmp(optarg, "high")) action->cvss_metrics->cre = CR_HIGH;
			else if (!strcmp(optarg, "not-defined")) action->cvss_metrics->cre = CR_NOT_DEFINED;
			else return -1;
			break;
		case 12:
			if (!strcmp(optarg, "low")) action->cvss_metrics->ire = IR_LOW;
			else if (!strcmp(optarg, "medium")) action->cvss_metrics->ire = IR_MEDIUM;
			else if (!strcmp(optarg, "high")) action->cvss_metrics->ire = IR_HIGH;
			else if (!strcmp(optarg, "not-defined")) action->cvss_metrics->ire = IR_NOT_DEFINED;
			else return -1;
			break;
		case 13:
			if (!strcmp(optarg, "low")) action->cvss_metrics->are = AR_LOW;
			else if (!strcmp(optarg, "medium")) action->cvss_metrics->are = AR_MEDIUM;
			else if (!strcmp(optarg, "high")) action->cvss_metrics->are = AR_HIGH;
			else if (!strcmp(optarg, "not-defined")) action->cvss_metrics->are = AR_NOT_DEFINED;
			else return -1;
			break;
		case 14:
			base++;
			action->cvss_metrics->base = atof(optarg);
			break;
		default:
			fprintf(stderr, "FOUND BAD OPTION %d :: %d :: %s\n", optind, optopt, argv[optind]);
			break;
		}
	}

	/* check parametres */
        if (action->op == OSCAP_OP_UNKNOWN) {
                print_cvss_usage("oscap", stderr, "Error: No operation specified");
                return -1;
        }

	if ( (action->op == OSCAP_OP_BASE || action->op == OSCAP_OP_ENV) &&
	     ( !ave || !ace || !aue || !cie || !iie || !aie) ) {
	        print_cvss_usage("oscap", stderr, "Error: Required metrics were not specified");
                return -1;
	}

	if ((action->op == OSCAP_OP_TEMP) && !base) {
	        print_cvss_usage("oscap", stderr, "Error: Base score was not specified");
                return -1;
	}

	return 0;
}

