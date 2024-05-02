//
// references
// https://www.slideshare.net/nttdata-tech/postgresql-extension-hook-pgunconf33-nttdata
//

#include "postgres.h"

#include "fmgr.h"
#include "tcop/utility.h"

PG_MODULE_MAGIC;

void _PG_init(void);
void _PG_fini(void);

static ProcessUtility_hook_type prev_ProcessUtility = NULL;

static void
prohibit_use_truncate(PlannedStmt* pstmt,
                      const char* queryString,
                      bool readOnlyTree,
                      ProcessUtilityContext context,
                      ParamListInfo params,
                      QueryEnvironment* queryEnv,
                      DestReceiver* dest,
                      QueryCompletion* qc)
{
  Node *parsetree = pstmt->utilityStmt;
  if (nodeTag(parsetree) == T_TruncateStmt)
    elog(ERROR, "do not use truncate");
  else
    standard_ProcessUtility(pstmt, queryString, readOnlyTree, context, params, queryEnv, dest, qc);
}

void _PG_init(void)
{
  prev_ProcessUtility = ProcessUtility_hook;
  ProcessUtility_hook = prohibit_use_truncate;
}

void _PG_fini(void)
{
  ProcessUtility_hook = prev_ProcessUtility;
}
