/* ========================================================================= *
 *                                                                           *
 *                 The Apache Software License,  Version 1.1                 *
 *                                                                           *
 *          Copyright (c) 1999-2001 The Apache Software Foundation.          *
 *                           All rights reserved.                            *
 *                                                                           *
 * ========================================================================= *
 *                                                                           *
 * Redistribution and use in source and binary forms,  with or without modi- *
 * fication, are permitted provided that the following conditions are met:   *
 *                                                                           *
 * 1. Redistributions of source code  must retain the above copyright notice *
 *    notice, this list of conditions and the following disclaimer.          *
 *                                                                           *
 * 2. Redistributions  in binary  form  must  reproduce the  above copyright *
 *    notice,  this list of conditions  and the following  disclaimer in the *
 *    documentation and/or other materials provided with the distribution.   *
 *                                                                           *
 * 3. The end-user documentation  included with the redistribution,  if any, *
 *    must include the following acknowlegement:                             *
 *                                                                           *
 *       "This product includes  software developed  by the Apache  Software *
 *        Foundation <http://www.apache.org/>."                              *
 *                                                                           *
 *    Alternately, this acknowlegement may appear in the software itself, if *
 *    and wherever such third-party acknowlegements normally appear.         *
 *                                                                           *
 * 4. The names  "The  Jakarta  Project",  "Jk",  and  "Apache  Software     *
 *    Foundation"  must not be used  to endorse or promote  products derived *
 *    from this  software without  prior  written  permission.  For  written *
 *    permission, please contact <apache@apache.org>.                        *
 *                                                                           *
 * 5. Products derived from this software may not be called "Apache" nor may *
 *    "Apache" appear in their names without prior written permission of the *
 *    Apache Software Foundation.                                            *
 *                                                                           *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED WARRANTIES *
 * INCLUDING, BUT NOT LIMITED TO,  THE IMPLIED WARRANTIES OF MERCHANTABILITY *
 * AND FITNESS FOR  A PARTICULAR PURPOSE  ARE DISCLAIMED.  IN NO EVENT SHALL *
 * THE APACHE  SOFTWARE  FOUNDATION OR  ITS CONTRIBUTORS  BE LIABLE  FOR ANY *
 * DIRECT,  INDIRECT,   INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL *
 * DAMAGES (INCLUDING,  BUT NOT LIMITED TO,  PROCUREMENT OF SUBSTITUTE GOODS *
 * OR SERVICES;  LOSS OF USE,  DATA,  OR PROFITS;  OR BUSINESS INTERRUPTION) *
 * HOWEVER CAUSED AND  ON ANY  THEORY  OF  LIABILITY,  WHETHER IN  CONTRACT, *
 * STRICT LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN *
 * ANY  WAY  OUT OF  THE  USE OF  THIS  SOFTWARE,  EVEN  IF  ADVISED  OF THE *
 * POSSIBILITY OF SUCH DAMAGE.                                               *
 *                                                                           *
 * ========================================================================= *
 *                                                                           *
 * This software  consists of voluntary  contributions made  by many indivi- *
 * duals on behalf of the  Apache Software Foundation.  For more information *
 * on the Apache Software Foundation, please see <http://www.apache.org/>.   *
 *                                                                           *
 * ========================================================================= */

/**
 * Manages the request mappings. It includes the internal mapper and all
 * properties associated with a location ( or virtual host ). The information
 * is set using:
 *   - various autoconfiguration mechanisms.
 *   - uriworkers.properties
 *   - JkMount directives
 *   - <SetHandler> and apache specific directives.
 *   - XXX workers.properties-like directives ( for a single config file )
 *   - other server-specific directives
 *
 * The intention is to allow the user to use whatever is more comfortable
 * and fits his needs. For 'basic' configuration the autoconf will be enough,
 * server-specific configs are the best for fine-tunning, properties are
 * easy to generate and edit.
 *
 *
 * Author: Gal Shachor <shachor@il.ibm.com>
 * author: Costin Manolache
 */
#ifndef JK_URIMAP_H
#define JK_URIMAP_H

#include "jk_global.h"
#include "jk_map.h"
#include "jk_logger.h"
#include "jk_uriEnv.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct jk_uriMap;
typedef struct jk_uriMap jk_uriMap_t;

struct jk_uriMap {
    /* map URI->WORKER */
    struct jk_uriEnv **maps;
    unsigned int size;
    unsigned int capacity;
    struct jk_workerEnv *workerEnv;
    
    /* ---------- Methods ---------- */

    int (*init)( jk_uriMap_t *_this,
                 struct jk_workerEnv *workerEnv,
                 jk_map_t *init_data );

    void (*destroy)( jk_uriMap_t *_this );

    jk_uriEnv_t *(*addMapping)( jk_uriMap_t *_this,
                                const char *vhost,
                                const char *uri,
                                const char *worker);

    /** Check the uri for potential security problems
     */
    int (*checkUri)( jk_uriMap_t *_this,
                     char *uri );

    struct jk_uriEnv *(*mapUri)(jk_uriMap_t *_this,
                                const char *vhost,
                                const char *uri );
    
    /* -------------------- @deprecated -------------------- */
    /* used by the mapper, temp storage ( ??? )*/

    /* Memory Pool */
    jk_pool_t           p;
    jk_pool_atom_t      buf[SMALL_POOL_SIZE];

    /* Temp Pool */
    jk_pool_t tp; 
    jk_pool_atom_t tbuf[SMALL_POOL_SIZE];
};
    
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* JK_URI_MAP_H */
