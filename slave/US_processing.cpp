#include "US_Processing.h"

US_Processing::US_Processing()
	: sen1Sig(false), sen2Sig(false), sen3Sig(false), sen1firstSig(0), sen2firstSig(0), sen3firstSig(0), sen1firstNonSig(0), sen2firstNonSig(0), sen3firstNonSig(0), sen1Out(0), sen2Out(0), sen3Out(0){}

void US_Processing::proccess(std::vector<float> sensorsTemp){

 // significant if >10 AND < 50
// if currently significant and becomes insignificant for less than 10 ms, ignore (error)
// if currently insignificant and becomes significant for less than 10 ms, ignore (error)

}


bool US_Proccessing::isSignificant(float test){
	return (test > 10 && test < 50);
}
