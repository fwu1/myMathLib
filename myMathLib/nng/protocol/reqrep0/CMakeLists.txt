#
# Copyright 2018 Staysail Systems, Inc. <info@staysail.tech>
# Copyright 2018 Capitar IT Group BV <info@capitar.com>
#
# This software is supplied under the terms of the MIT License, a
# copy of which should be located in the distribution where this
# file was obtained (LICENSE.txt).  A copy of the license may also be
# found online at https://opensource.org/licenses/MIT.
#

#  Req/Rep protocol
option (NNG_PROTO_REQ0 "Enable REQv0 protocol." ON)
mark_as_advanced(NNG_PROTO_REQ0)

option (NNG_PROTO_REP0 "Enable REPv0 protocol." ON)
mark_as_advanced(NNG_PROTO_REP0)

set(_DEFS)
set(_SRCS)
set(_HDRS)

if (NNG_PROTO_REQ0)
    list(APPEND _DEFS -DNNG_HAVE_REQ0)
    list(APPEND _SRCS
        protocol/reqrep0/req.c protocol/reqrep0/xreq.c
        protocol/reqrep0/req.h)
    list(APPEND _HDRS protocol/reqrep0/req.h)
endif()

if (NNG_PROTO_REP0)
    list(APPEND _DEFS -DNNG_HAVE_REP0)
    list(APPEND _SRCS
        protocol/reqrep0/rep.c protocol/reqrep0/xrep.c
        protocol/reqrep0/rep.h)
    list(APPEND _HDRS protocol/reqrep0/rep.h)
endif()

set(NNG_DEFS ${NNG_DEFS} ${_DEFS} PARENT_SCOPE)
set(NNG_SRCS ${NNG_SRCS} ${_SRCS} PARENT_SCOPE)
set(NNG_HDRS ${NNG_HDRS} ${_HDRS} PARENT_SCOPE)
