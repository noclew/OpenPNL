#ifndef __TOKENCOVER_HPP__
#define __TOKENCOVER_HPP__

#include <map>
#include "pnlHighConf.hpp"
#include "pnlTok.hpp"
#include "ModelEngine.hpp"

// FORWARDS
struct TokIdNode;
class WGraph;
class WDistribFun;

namespace pnl
{
    class CPNLBase;
    class CGraph;
    class pnlString;
};

class PNLHIGH_API TokenCover: public ModelEngine
{
public:
    TokenCover(TokIdNode *root, WGraph *graph);
    TokenCover(const char *rootName, WGraph *graph, bool bAutoNum = false);
    TokenCover(const char *rootName, const TokenCover &tokCovFrom, bool bAutoNum = false);
    ~TokenCover();
    TokIdNode *Root() const { return m_pRoot; }
    void Resolve(Tok &tok) const;
    void Resolve(TokArr &aTok) const;

    int AddNode(String &nodeName);
    void AddNode(TokArr &nodes, TokArr &values);
    int AddNode(Tok &node, TokArr &values);
    bool DelNode(int iNode);
    bool DelNode(Tok &nodeName);
    int nValue(int iNode);
    void GetValues(int iNode, Vector<String> &aValue);
    void SetValues(int iNode, const Vector<String> &aValue);

    String Value(int iNode, int iValue) const;
    void SetValue(int iNode, int iValue, String &value);

    TokIdNode *Node(int iNode) const;
    TokIdNode *Node(Tok &node) const;
    Vector<TokIdNode*> Nodes(Vector<int> aiNode);
    WGraph *Graph() const { return m_pGraph; }

    // from BayesNet
    void RenameGraph(const int *renaming);
    Vector<TokIdNode*> ExtractNodes(TokArr &aValue) const;
    int NodesClassification(TokArr &aValue) const;

    // Properties support
    void AddProperty(const char *name, const char **aValue, int nValue);
    void GetPropertyVariants(const char *name, Vector<String> &aValue) const;

protected:
    virtual void DoNotify(int message, int iNode, ModelEngine *pObj);
    virtual int InterestedIn() const { return eDelNode|eChangeName; }

private:// FUNCTIONS
    void CreateRoot(const char *rootName, bool bAutoNum = false);
    static bool CopyRecursive(TokIdNode *to, const TokIdNode *from);
    void SetValues(TokIdNode *node, const Vector<String> &aValue, int iNode);
    void KillChildren(TokIdNode *node);
    void TuneNodeValue(TokIdNode *pValue, int iValue);
    TokIdNode *NodeValue(int iNode, int iValue) const;

private:// DATA
    // Tree for any net:
    //
    //		   / categoric
    //  net - nodes
    //		   \ continuous
    TokIdNode *m_pRoot;		// pointer to root node of bnet
    TokIdNode *m_aNode;		// pointer to node of all bnet nodes
    TokIdNode *m_pCategoric;	// pointer to parent node for all categoric nodes
    TokIdNode *m_pContinuous;	// pointer to parent node for all continuous nodes
    TokIdNode *m_pDefault;	// pointer to default node
    TokIdNode *m_pProperties;	// pointer to properties namespace
    WGraph *m_pGraph;		// serve graph and naming
};

#endif //__TOKENCOVER_HPP__