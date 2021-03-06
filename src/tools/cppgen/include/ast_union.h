/*

COPYRIGHT

Copyright 1992, 1993, 1994 Sun Microsystems, Inc.  Printed in the United
States of America.  All Rights Reserved.

This product is protected by copyright and distributed under the following
license restricting its use.

The Interface Definition Language Compiler Front End (CFE) is made
available for your use provided that you include this license and copyright
notice on all media and documentation and the software program in which
this product is incorporated in whole or part. You may copy and extend
functionality (but may not remove functionality) of the Interface
Definition Language CFE without charge, but you are not authorized to
license or distribute it to anyone else except as part of a product or
program developed by you or with the express written consent of Sun
Microsystems, Inc. ("Sun").

The names of Sun Microsystems, Inc. and any of its subsidiaries or
affiliates may not be used in advertising or publicity pertaining to
distribution of Interface Definition Language CFE as permitted herein.

This license is effective until terminated by Sun for failure to comply
with this license.  Upon termination, you shall destroy or return all code
and documentation for the Interface Definition Language CFE.

INTERFACE DEFINITION LANGUAGE CFE IS PROVIDED AS IS WITH NO WARRANTIES OF
ANY KIND INCLUDING THE WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS
FOR A PARTICULAR PURPOSE, NONINFRINGEMENT, OR ARISING FROM A COURSE OF
DEALING, USAGE OR TRADE PRACTICE.

INTERFACE DEFINITION LANGUAGE CFE IS PROVIDED WITH NO SUPPORT AND WITHOUT
ANY OBLIGATION ON THE PART OF Sun OR ANY OF ITS SUBSIDIARIES OR AFFILIATES
TO ASSIST IN ITS USE, CORRECTION, MODIFICATION OR ENHANCEMENT.

SUN OR ANY OF ITS SUBSIDIARIES OR AFFILIATES SHALL HAVE NO LIABILITY WITH
RESPECT TO THE INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY
INTERFACE DEFINITION LANGUAGE CFE OR ANY PART THEREOF.

IN NO EVENT WILL SUN OR ANY OF ITS SUBSIDIARIES OR AFFILIATES BE LIABLE FOR
ANY LOST REVENUE OR PROFITS OR OTHER SPECIAL, INDIRECT AND CONSEQUENTIAL
DAMAGES, EVEN IF SUN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

Use, duplication, or disclosure by the government is subject to
restrictions as set forth in subparagraph (c)(1)(ii) of the Rights in
Technical Data and Computer Software clause at DFARS 252.227-7013 and FAR
52.227-19.

Sun, Sun Microsystems and the Sun logo are trademarks or registered
trademarks of Sun Microsystems, Inc.

SunSoft, Inc.  
2550 Garcia Avenue 
Mountain View, California  94043

NOTE:

SunOS, SunSoft, Sun, Solaris, Sun Microsystems or the Sun logo are
trademarks or registered trademarks of Sun Microsystems, Inc.

*/

#ifndef _AST_UNION_AST_UNION_HH
#define _AST_UNION_AST_UNION_HH


// Representation of union declaration:
//
// NOTE: add(AST_ConcreteType *) is defined here because a union
// can contain locally defined types in addition to fields.
//
// NOTE: add(AST_EnumValue *) is defined here because enums can
// be defined manifest locally; the constants defined in these
// enums are inserted in the enclosing scope. It is unlikely that
// a BE writer will need to overload this function in AST_Union.

/*
** DEPENDENCIES: ast_concrete_type.hh, utl_scope.hh, ast_union_branch.hh,
**   ast_union_label.hh, utl_scoped_name.hh, utl_strlist.hh
**
** USE: Included from ast.hh
*/

class AST_Union : public virtual AST_Structure
{
public:

   AST_Union ();
   AST_Union 
   (
      UTL_ScopedName * n,
      const UTL_Pragmas & p
   );
   virtual ~AST_Union () {}

   AST_ConcreteType * disc_type ();
   void set_disc_type (AST_ConcreteType * dt);
   AST_Expression::ExprType udisc_type ();

   DEF_NARROW_METHODS1 (AST_Union, AST_Structure);
   DEF_NARROW_FROM_DECL (AST_Union);
   DEF_NARROW_FROM_SCOPE (AST_Union);

   bool is_defined () { return pd_defined; };
   void set_defined (bool def) { pd_defined = def; };

   virtual void update_type ();
   virtual void dump (ostream &);

private:

   // Data

   AST_ConcreteType *pd_disc_type; // Discriminator type
   AST_Expression::ExprType pd_udisc_type; // Its expression type

   // Look up a branch by node pointer

   AST_UnionBranch *lookup_branch(AST_UnionBranch *branch);

   // Look up the branch with the "default" label

   AST_UnionBranch *lookup_default();

   // Look up a branch given a branch with a label. This is used to
   // check for duplicate labels

   AST_UnionBranch *lookup_label(AST_UnionBranch *b);

   // Look up a union branch given an enumerator. This is used to
   // check for duplicate enum labels

   AST_UnionBranch *lookup_enum(AST_UnionBranch *b);

   friend int yyparse();

   virtual AST_Union *fe_add_union(AST_Union *u);
   virtual AST_UnionBranch *fe_add_union_branch(AST_UnionBranch *b);
   virtual AST_Structure *fe_add_structure(AST_Structure *s);
   virtual AST_Enum *fe_add_enum(AST_Enum *e);
   virtual AST_EnumVal *fe_add_enum_val(AST_EnumVal *v);
   virtual AST_Typedef *fe_add_typedef(AST_Typedef *t);

   bool pd_defined;
};

#endif
