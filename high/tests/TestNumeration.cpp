#include "test_conf.hpp"
#include "pnlException.hpp"
#include "pnl_dll.hpp"
PNLW_USING

BayesNet *GetSimpleTabularModelWithEntanglementNumeration()
{
    // One  Two
    //   |  |
    //   \/\/
    //   Zero
    BayesNet *net;
    net = new BayesNet();

    net->AddNode(discrete^"Zero One Two", "State1 State2");
    net->AddArc("One Two", "Zero");
    
    net->SetPTabular("One^State1", "0.5");
    net->SetPTabular("One^State2", "0.5");
    net->SetPTabular("Two^State1", "0.4");
    net->SetPTabular("Two^State2", "0.6");
    net->SetPTabular("Zero^State1","0.1" ,"One^State1 Two^State1");
    net->SetPTabular("Zero^State2","0.9" ,"One^State1 Two^State1");
    net->SetPTabular("Zero^State1","0.2" ,"One^State1 Two^State2");
    net->SetPTabular("Zero^State2","0.8" ,"One^State1 Two^State2");
    net->SetPTabular("Zero^State1","0.3" ,"One^State2 Two^State1");
    net->SetPTabular("Zero^State2","0.7" ,"One^State2 Two^State1");
    net->SetPTabular("Zero^State1","0.8" ,"One^State2 Two^State2");
    net->SetPTabular("Zero^State2","0.2" ,"One^State2 Two^State2");

    return net;
}

BayesNet *GetSimpleTabularModelWithDeletedElement()
{
    // One  Two (deleted) Three
    //   |         |     |
    //   |         \/    |
    //   o------>Zero<---o
    BayesNet *net;
    net = new BayesNet();

    net->AddNode(discrete^"One Three Zero", "State1 State2");
    //net->DelNode("Two");
    net->AddArc("One Three", "Zero");
    
    net->SetPTabular("One^State1", "0.5");
    net->SetPTabular("One^State2", "0.5");
    net->SetPTabular("Three^State1", "0.4");
    net->SetPTabular("Three^State2", "0.6");
    net->SetPTabular("Zero^State1","0.1" ,"One^State1 Three^State1");
    net->SetPTabular("Zero^State2","0.9" ,"One^State1 Three^State1");
    net->SetPTabular("Zero^State1","0.2" ,"One^State1 Three^State2");
    net->SetPTabular("Zero^State2","0.8" ,"One^State1 Three^State2");
    net->SetPTabular("Zero^State1","0.3" ,"One^State2 Three^State1");
    net->SetPTabular("Zero^State2","0.7" ,"One^State2 Three^State1");
    net->SetPTabular("Zero^State1","0.8" ,"One^State2 Three^State2");
    net->SetPTabular("Zero^State2","0.2" ,"One^State2 Three^State2");

    return net;
}

void TestForGetPTabular()
{
    BayesNet *net = GetSimpleTabularModelWithEntanglementNumeration();

    //TokArr BayesNet::GetPTabular(TokArr child, TokArr parents)
    TokArr Zero = net->GetPTabular("Zero");
    TokArr One = net->GetPTabular("One");
    TokArr Two = net->GetPTabular("Two");

    std::cout << Zero << "\n";
    std::cout << One << "\n";
    std::cout << Two << "\n";

    if ((Zero[0].FltValue() != 0.1f)||(Zero[1].FltValue() != 0.9f)||
	(Zero[2].FltValue() != 0.2f)||(Zero[3].FltValue() != 0.8f)||
	(Zero[4].FltValue() != 0.3f)||(Zero[5].FltValue() != 0.7f)||
	(Zero[6].FltValue() != 0.8f)||(Zero[7].FltValue() != 0.2f))
    {
	PNL_THROW(pnl::CAlgorithmicException, "There is error in the function TestForGetPTabular 1");
    };

    if ((One[0].FltValue() != 0.5f)||(One[1].FltValue() != 0.5f))
    {
	PNL_THROW(pnl::CAlgorithmicException, "There is error in the function TestForGetPTabular 2");
    };

    if ((Two[0].FltValue() != 0.4f)||(Two[1].FltValue() != 0.6f))
    {
	PNL_THROW(pnl::CAlgorithmicException, "There is error in the function TestForGetPTabular 3");
    };
}

void TestForSetInferenceProperties()
{
    BayesNet *net = GetSimpleTabularModelWithEntanglementNumeration();

    net->SetProperty("Inference","gibbs");
    //net->SetProperty("GibbsNumberOfIterations","1000");
    //net->SetProperty("GibbsNumberOfStreams","2");
    //net->SetProperty("GibbsThresholdIteration","100");

    net->GetJPD("One");
}