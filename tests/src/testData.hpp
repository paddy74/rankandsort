#pragma once

#include <lowletorfeats/base/stdDef.hpp>
#include <string>
#include <vector>

std::pair<std::string, std::vector<lowletorfeats::base::StrStrMap> >
    getTestData()
{
    typedef lowletorfeats::base::StrStrMap StrStrMap;

    std::string const queryString = "Time to query hello word!";

    // Construct raw data
    std::vector<StrStrMap> structDocTextVector{
        lowletorfeats::base::StrStrMap{
            {"id", "0"},
            {"rscore", "1"},
            {"url", "https://arxiv.org/pdf/1904.12735.pdf"},
            {"title",
             "DeepHMap++: Combined Projection Grouping and Correspondence "
             "Learning for Full DoF Pose Estimation"},
            {"author", "Mingliang Fu and Weijia Zhou"},
            {"anchor", "fumingliang@aliyun.com"},
            {"body",
             "In recent years, estimating the 6D pose of object instances "
             "with convolutional neural network(CNN) has received "
             "considerable attention.  Depending on whether intermediate cues "
             "are used, therelevant literature can be roughly divided into "
             "two broad categories:  direct methods and two-stagepipelines. "
             "For the latter, intermediate cues, such as 3D object "
             "coordinates, semantic keypoints, or virtualcontrol points "
             "instead of pose parameters are regressed by CNN in the first "
             "stage. Object pose can thenbe solved by correspondence "
             "constraints constructed with these intermediate cues.  In this "
             "paper, wefocus on the postprocessing of a two-stage pipeline "
             "and propose to combine two learning concepts forestimating "
             "object pose under challenging scenes: projection grouping on "
             "one side, and correspondencelearning on the other.  We firstly "
             "employ a local-patch based method to predict projection "
             "heatmapswhich denote the confidence distribution of projection "
             "of 3D bounding box’s corners.  A projectiongrouping module is "
             "then proposed to remove redundant local maxima from each layer "
             "of heatmaps.Instead of directly feeding 2D–3D correspondences "
             "to the perspective-n-point (PnP) algorithm, "
             "multiplecorrespondence hypotheses are sampled from local maxima "
             "and its corresponding neighborhood andranked by a "
             "correspondence–evaluation network. Finally, correspondences "
             "with higher confidence areselected to determine object pose. "
             "Extensive experiments on three public datasets demonstrate that "
             "theproposed framework outperforms several state of the art "
             "methods"}},
        lowletorfeats::base::StrStrMap{
            {"id", "1"},
            {"rscore", "0"},
            {"url", "https://arxiv.org/pdf/1904.12589.pdf"},
            {"title",
             "A dual branch deep neural network forclassification and "
             "detection in mammograms"},
            {"author", "Ran Bakalo, Jacob Goldberger and Rami Ben-Ari"},
            {"anchor", "ranba@il.ibm.com"},
            {"body",
             "In  this  paper,  we  propose  a  novel  deep  "
             "learningarchitecture  for  joint  classification  and  "
             "localization  of  abnor-malities  in  mammograms.  We  first  "
             "assume  a  weakly  supervisedsetting  and  present  a  new  "
             "approach  with  data  driven  decisions.This novel network "
             "combines two learning branches with region-level  "
             "classification  and  region  ranking.  The  network  provides  "
             "aglobal  classification  of  the  image  into  multiple  "
             "classes,  such  asmalignant,  benign  or  normal.  Our  method  "
             "further  enables  thelocalization of abnormalities as global "
             "class discriminative regionsin  full  mammogram  resolution.  "
             "Next,  we  extend  this  methodto  a  semi-supervised  setting  "
             "that  engages  a  small  set  of  localannotations, using a "
             "novel architecture, and a multi-task objectivefunction.  We  "
             "present  the  impact  of  the  local  annotations  onseveral "
             "performance measures, including localization, to evaluatethe "
             "cost effectiveness of lesion annotation effort. Our "
             "evaluationis  made  over  a  large  multi-center  mammography  "
             "dataset  of∼3,000 mammograms with various findings. "
             "Experimental resultsdemonstrate  the  capabilities  and  "
             "advantages  of  the  proposedmethod   over   previous   "
             "weakly-supervised   strategies,   and   theimpact  of  "
             "semi-supervised  learning.  We  show  that  targeting  "
             "theannotation  of  only  5%  of  the  images  can  "
             "significantly  boost performance."}}};

    // Construct analyzed data

    return std::pair(queryString, structDocTextVector);
}
