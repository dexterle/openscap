/*! 
 *  \addtogroup CVSS
 *  \{
 *
 *  \file cvsscalc.h
 *  \brief Interface to Common Vulnerability Scoring System Version 2
 *  
 *  See details at http://nvd.nist.gov/cvss.cfm
 *
 */

/*
 * Copyright 2008 Red Hat Inc., Durham, North Carolina.
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
 *      Tomas Heinrich <theinric@redhat.com>
 *      Peter Vrabec   <pvrabec@redhat.com>
 *      Brandon Dixon  <Brandon.Dixon@g2-inc.com>
 */


#ifndef _CVSSCALC_H_
#define _CVSSCALC_H_

#include <stdbool.h>

struct cvss_entry;

struct cvss_entry * cvss_entry_new(void);
void cvss_entry_free(struct cvss_entry * entry);

const char* cvss_entry_get_score(const struct cvss_entry * entry);
const char* cvss_entry_get_AV(const struct cvss_entry * entry);
const char* cvss_entry_get_AC(const struct cvss_entry * entry);
const char* cvss_entry_get_authentication(const struct cvss_entry * entry);
const char* cvss_entry_get_imp_confidentiality(const struct cvss_entry * entry);
const char* cvss_entry_get_imp_integrity(const struct cvss_entry * entry);
const char* cvss_entry_get_imp_availability(const struct cvss_entry * entry);
const char* cvss_entry_get_source(const struct cvss_entry * entry);
const char* cvss_entry_get_generated(const struct cvss_entry * entry);

bool cvss_entry_set_score(struct cvss_entry *entry, const char *new_score);
bool cvss_entry_set_AV(struct cvss_entry *entry, const char *new_AV);
bool cvss_entry_set_AC(struct cvss_entry *entry, const char *new_AC);
bool cvss_entry_set_authentication(struct cvss_entry *entry, const char *new_authentication);
bool cvss_entry_set_imp_confidentiality(struct cvss_entry *entry, const char *new_item);
bool cvss_entry_set_imp_integrity(struct cvss_entry *entry, const char *new_item);
bool cvss_entry_set_imp_availability(struct cvss_entry *entry, const char *new_item);
bool cvss_entry_set_source(struct cvss_entry *entry, const char *new_source);
bool cvss_entry_set_generated(struct cvss_entry *entry, const char *new_generated);

//! Access Vector
/*! This metric reflects how the vulnerability is exploited. */
typedef enum {
	AV_LOCAL,            /*!< requires local access */
	AV_ADJACENT_NETWORK, /*!< adjacent network accessible */
	AV_NETWORK           /*!< network accessible */
} cvss_access_vector_t;

//! Access Complexity
/*! This metric measures the complexity of the attack required to exploit the 
 *  vulnerability once an attacker has gained access to the target system. 
 */
typedef enum {
	AC_HIGH,
	AC_MEDIUM,
	AC_LOW
} cvss_access_complexity_t;

//! Authentication 
/*! This metric measures the complexity of the attack required to exploit 
 *  the vulnerability once an attacker has gained access to the target system. 
 */
typedef enum {
	AU_NONE,             /*!< requires multiple authentication instances */
	AU_SINGLE_INSTANCE,  /*!< requires single instance of authentication */
	AU_MULTIPLE_INSTANCE /*!< requires no authentication */
} cvss_authentication_t;

//! Confidentiality Impact
/*! This metric measures the impact on confidentiality of a successfully 
 *  exploited vulnerability.
 */
typedef enum {
	CI_NONE,
	CI_PARTIAL,
	CI_COMPLETE
} cvss_conf_impact_t;

//! Integrity Impact
/*! This metric measures the impact to integrity of a successfully exploited 
 *  vulnerability.
 */
typedef enum {
	II_NONE,
	II_PARTIAL,
	II_COMPLETE
} cvss_integ_impact_t;

//! Availability Impact
/*! This metric measures the impact to availability of a successfully 
 *  exploited vulnerability. 
 */
typedef enum {
	AI_NONE,
	AI_PARTIAL,
	AI_COMPLETE
} cvss_avail_impact_t;

//! Exploitability
/*! This metric measures the current state of exploit techniques or code 
 *  availability. 
 */
typedef enum {
	EX_UNPROVEN,
	EX_PROOF_OF_CONCEPT,
	EX_FUNCTIONAL,
	EX_HIGH,
	EX_NOT_DEFINED
} cvss_exploitability_t;

//! Remediation Level
/*! The remediation level of a vulnerability is an important factor for 
 *  prioritization.
 */
typedef enum {
	RL_OFFICIAL_FIX,
	RL_TEMPORARY_FIX,
	RL_WORKAROUND,
	RL_UNAVAILABLE,
	RL_NOT_DEFINED
} cvss_remediation_level_t;

//! Report Confidence
/*! This metric measures the degree of confidence in the existence 
 *  of the vulnerability and the credibility of the known 
 *  technical details. 
 */
typedef enum {
	RC_UNCONFIRMED,
	RC_UNCORROBORATED,
	RC_CONFIRMED,
	RC_NOT_DEFINED
} cvss_report_confidence_t;

//! Collateral Damage Potential 
/*! This metric measures the potential for loss of life or physical assets 
 *  through damage or theft of property or equipment. 
 */
typedef enum {
	CD_NONE,
	CD_LOW,
	CD_LOW_MEDIUM,
	CD_MEDIUM_HIGH,
	CD_HIGH,
	CD_NOT_DEFINED
} cvss_collateral_damage_potential_t;

//! Target Distribution 
/*! This metric measures the proportion of vulnerable systems. It is meant 
 *  as an environment-specific indicator in order to approximate the percentage 
 *  of systems that could be affected by the vulnerability.
 */
typedef enum {
	TD_NONE,
	TD_LOW,
	TD_MEDIUM,
	TD_HIGH,
	TD_NOT_DEFINED
} cvss_target_distribution_t;

//! Confidentiality Requirement
/*! This metric enable the analyst to customize the CVSS score depending on 
 *  the importance of the affected IT asset to a user’s organization, 
 *  measured in term of confidentiality.
 */
typedef enum {
	CR_LOW,
	CR_MEDIUM,
	CR_HIGH,
	CR_NOT_DEFINED
} cvss_conf_req_t;

//! Integrity Requirement
/*! This metric enable the analyst to customize the CVSS score depending on 
 *  the importance of the affected IT asset to a user’s organization, 
 *  measured in term of integrity.
 */
typedef enum {
	IR_LOW,
	IR_MEDIUM,
	IR_HIGH,
	IR_NOT_DEFINED
} cvss_integ_req_t;

//! Availabublity Requirement
/*! This metric enable the analyst to customize the CVSS score depending on 
 *  the importance of the affected IT asset to a user’s organization, 
 *  measured in term of availability.
 */
typedef enum {
	AR_LOW,
	AR_MEDIUM,
	AR_HIGH,
	AR_NOT_DEFINED
} cvss_avail_req_t;

/*! \fn cvss_base_score(cvss_access_vector_t ave, cvss_access_complexity_t ace, cvss_authentication_t aue,
 *                      cvss_conf_impact_t   cie, cvss_integ_impact_t      iie, cvss_avail_impact_t    aie,
 *                      double *base_score,
 *                      double *impact_score,
 *                      double *exploitability_score)
 */
int cvss_base_score(cvss_access_vector_t ave, cvss_access_complexity_t ace, cvss_authentication_t aue,
                    cvss_conf_impact_t   cie, cvss_integ_impact_t      iie, cvss_avail_impact_t   aie, 
                    double *base_score, 
                    double *impact_score, 
                    double *exploitability_score);

/*! \fn cvss_temp_score(cvss_exploitability_t   exe, cvss_remediation_level_t rle, 
 *                      cvss_report_confidence_t rce, double             base_score, 
 *                      double             *temporal_score);
 */
int cvss_temp_score(cvss_exploitability_t    exe, cvss_remediation_level_t rle, 
                    cvss_report_confidence_t rce, double             base_score, 
                    double             *temporal_score);

/*! \fn cvss_env_score(cvss_collateral_damage_potential_t cde, cvss_target_distribution_t   tde, 
 *                     cvss_conf_req_t                    cre, cvss_integ_req_t             ire, 
 *                     cvss_avail_req_t                   are, double *enviromental_score,
 *	                   cvss_access_vector_t               ave, cvss_access_complexity_t     ace, 
 *                     cvss_authentication_t              aue, cvss_conf_impact_t           cie, 
 *                     cvss_integ_impact_t                iie, cvss_avail_impact_t          aie,	     
 *                     cvss_exploitability_t              exe, cvss_remediation_level_t     rle, 
 *                     cvss_report_confidence_t           rce);
 */
int cvss_env_score(cvss_collateral_damage_potential_t cde, cvss_target_distribution_t   tde, 
                   cvss_conf_req_t                    cre, cvss_integ_req_t             ire, 
                   cvss_avail_req_t                   are, double *enviromental_score,
                   cvss_access_vector_t               ave, cvss_access_complexity_t     ace, 
                   cvss_authentication_t              aue, cvss_conf_impact_t           cie, 
                   cvss_integ_impact_t                iie, cvss_avail_impact_t          aie,	     
                   cvss_exploitability_t              exe, cvss_remediation_level_t     rle, 
                   cvss_report_confidence_t           rce);

#endif /* _CVSSCALC_H_ */
