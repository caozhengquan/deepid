//#include <vector>

//#include "caffe/filler.hpp"
//#include "caffe/layers/center_loss_layer.hpp"
//#include "caffe/util/math_functions.hpp"

//namespace caffe {

//template <typename Dtype>
//void CenterLossLayer<Dtype>::LayerSetUp(const vector<Blob<Dtype>*>& bottom,
      //const vector<Blob<Dtype>*>& top) {
  //const int num_output = this->layer_param_.center_loss_param().num_output();
  //// alpha
  //margin_ = this->layer_param_.center_loss_param().margin();
  //N_ = num_output;
  //const int axis = bottom[0]->CanonicalAxisIndex(
      //this->layer_param_.center_loss_param().axis());
  //// Dimensions starting from "axis" are "flattened" into a single
  //// length K_ vector. For example, if bottom[0]'s shape is (N, C, H, W),
  //// and axis == 1, N inner products with dimension CHW are performed.
  //K_ = bottom[0]->count(axis);
  //// Check if we need to set up the weights
  //if (this->blobs_.size() > 0) {
    //LOG(INFO) << "Skipping parameter initialization";
  //} else {
    //this->blobs_.resize(1);
    //// Intialize the weight
    //vector<int> center_shape(2);
    //center_shape[0] = N_;
    //center_shape[1] = K_;
    //this->blobs_[0].reset(new Blob<Dtype>(center_shape));
    //// fill the weights
    //shared_ptr<Filler<Dtype> > center_filler(GetFiller<Dtype>(
        //this->layer_param_.center_loss_param().center_filler()));
    //center_filler->Fill(this->blobs_[0].get());

  //}  // parameter initialization
  //this->param_propagate_down_.resize(this->blobs_.size(), true);
//}

//template <typename Dtype>
//void CenterLossLayer<Dtype>::Reshape(const vector<Blob<Dtype>*>& bottom,
      //const vector<Blob<Dtype>*>& top) {
  //CHECK_EQ(bottom[1]->channels(), 1);
  //CHECK_EQ(bottom[1]->height(), 1);
  //CHECK_EQ(bottom[1]->width(), 1);
  //M_ = bottom[0]->num();
  //// The top shape will be the bottom shape with the flattened axes dropped,
  //// and replaced by a single axis with dimension num_output (N_).
  //LossLayer<Dtype>::Reshape(bottom, top);
  //distance_.ReshapeLike(*bottom[0]);
  //variation_sum_.ReshapeLike(*this->blobs_[0]);

  //vector<int> mat_shape(1);
  //mat_shape[0] = M_ * M_;
  //mat_.Reshape(mat_shape);
  //distance_norm_mat_.ReshapeLike(mat_);
  //lij_.ReshapeLike(mat_);

  //vector<int> distance_mat_shape(2);
  //distance_mat_shape[0] = M_ * M_;
  //distance_mat_shape[1] = K_;
  //distance_mat_.Reshape(distance_mat_shape);

  //vector<int> If_shape(2);
  //If_shape[0] = K_;
  //If_shape[1] = M_ * K_;
  //If_.Reshape(If_shape);
  //Dtype* If_data = If_.mutable_cpu_data();
  //caffe_set(If_.count(), Dtype(0), If_data);
  //for (int i = 0; i < K_; i++) {
    //for (int j = i; j < M_ * K_; j = j + K_) {
      //If_data[i * (M_ * K_) + j] = Dtype(1);
    //}
  //}

  //Ic_.ReshapeLike(*bottoms[1]);
  //Dtype* Ic_data = Ic_.mutable_cpu_data();
  //caffe_set(Ic_.count(), Dtype(1), Ic_data);

  //Ia_.ReshapeLike(mat_);
  //Dtype* Ia_data = Ia_.mutable_cpu_data();
  //caffe_set(Ia_.count(), Dtype(1), Ia_data);

  //vector<int> Ib_shape(2);
  //Ib_shape[0] = M_;
  //Ib_shape[1] = M_ * M_;
  //Ib_.Reshape(Ib_shape);
  //Dtype* Ib_data = Ib_.mutable_cpu_data();
  //caffe_set(Ib_.count(), Dtype(0), Ib_data);
  //for (int i = 0; i < M_; i++) {
    //for (int j = i * M_; j < (i + 1) * M_; j++) {
      //Ib_data[i * (M_ * M_) + j] = Dtype(1);
    //}
  //}

  //vector<int> Im_shape(1);
  //Im_shape[0] = K_;
  //Im_.Reshape(Im_shape);
  //Dtype* Im_data = Im_.mutable_cpu_data();
  //caffe_set(Im_.count(), Dtype(1), Im_data);
//}

//template <typename Dtype>
//void CenterLossLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
    //const vector<Blob<Dtype>*>& top) {
  //const Dtype* bottom_data = bottom[0]->cpu_data();
  //const Dtype* label = bottom[1]->cpu_data();
  //const Dtype* center = this->blobs_[0]->cpu_data();
  //Dtype* distance_data = distance_.mutable_cpu_data();

  //Dtype* mat_data = mat_.mutable_cpu_data();
  //Dtype* distance_norm_mat_data = distance_norm_mat_.mutable_cpu_data();
  //Dtype* lij_data = lij_.mutable_cpu_data();
  //Dtype* distance_mat_data = distance_mat_.mutable_cpu_data();

  //Blob<Dtype> cy;
  //cy.ReshapeLike(*bottom[0]);

  //Blob<Dtype> xi, cyj;
  //xi.ReshapeLike(distance_mat_);
  //cyj.ReshapeLike(distance_mat_);

  //// the i-th distance_data
  //for (int i = 0; i < M_; i++) {
    //const int label_value = static_cast<int>(label[i]);
    //// D(i,:) = X(i,:) - C(y(i),:)
    //caffe_sub(K_, bottom_data + i * K_, center + label_value * K_, distance_data + i * K_);

    //// [cy0; cy1; ...; cy(M - 1)] => cy
    //caffe_copy(K_, center + label_value * K_, cy.mutable_cpu_data() + i * K_);
    //for (int j = 0; j < M_; j++) {
      //const int label_value_j = static_cast<int>(label[j]);
      //if (label_value_j == label_value) {
        //lij_data[i * M_ + j] = Dtype(1);
      //}
      //else {
        //lij_data[i * M_ + j] = Dtype(-1);
      //}
    //}
  //}
  //// Dtype dot = caffe_cpu_dot(M_ * K_, distance_.cpu_data(), distance_.cpu_data());
  //// cyj = [cy; cy; ...; cy]
  //caffe_cpu_gemm<Dtype>(CblasNoTrans, CblasNoTrans, M_, M_ * K_, 1, 1, Ic_.cpu_data(), cy.cpu_data(), 0., cyj.mutable_cpu_data());
  //// cyi = [cy0; cy0; ...; cy0; cy1; cy1; ...; cy1; ...; cy(M - 1); cy(M - 1); ...; cy(M - 1)]
  //// caffe_cpu_gemm<Dtype>(CblasNoTrans, CblasNoTrans, M_, M_ * K_, K_, 1, cy.cpu_data(), If_.cpu_data(), 0., cyi.mutable_cpu_data());
  //// cyi - cyj
  //// caffe_sub(distance_mat_.count(), cyi.cpu_data(), cyj.cpu_data(), distance_mat_data);

  //// Blob<Dtype> ipjm2x;
  //// ipjm2x.ReshapeLike(distance_mat_);
  //// cyi + cyj
  //// caffe_add(distance_mat_.count(), cyi.cpu_data(), cyj.cpu_data(), ipjm2x.mutable_cpu_data());
  //// xi = [x0; x0; ...; x0; x1; x1; ...; x1; x(M - 1); x(M - 1); ...; x(M - 1)]
  //caffe_cpu_gemm<Dtype>(CblasNoTrans, CblasNoTrans, M_, M_ * K_, K_, 1, bottom_data, If_.cpu_data(), 0., xi.mutable_cpu_data());
  //// xi - cyj
  //caffe_sub(distance_mat_.count(), xi.cpu_data(), cyj.cpu_data(), distance_mat_data);

  //// Blob<Dtype> ipj2;
  //// ipj2.ReshapeLike(distance_mat_);
  //// (xi - cyj) .* (xi - cyj)
  //Blob<Dtype> distance_square;
  //distance_square.ReshapeLike(distance_mat_);
  //caffe_powx(distance_mat_.count(), distance_mat_.cpu_data(), Dtype(2), distance_square.mutable_cpu_data());

  //Blob<Dtype> pa;
  //pa.ReshapeLike(mat_);
  //// (xi - cyj)T(xi - cyj)
  //caffe_cpu_gemv<Dtype>(CblasNoTrans, M_ * M_, K_, 1., distance_square.cpu_data(), Im_.cpu_data(), 0., distance_norm_mat_data);
  //// ||xi - cyj||
  //caffe_powx(mat_.count(), distance_norm_mat_.cpu_data(), Dtype(0.5), distance_norm_mat_data);
  //// ||xi - cyj|| - 1
  //caffe_sub(mat_.count(), distance_norm_mat_.cpu_data(), Ia_.cpu_data(), pa.mutable_cpu_data());
  //// lij(||xi - cyj|| - 1)
  //caffe_mul(mat_.count(), lij_.cpu_data(), pa.cpu_data(), pa.mutable_cpu_data());
  //// lij(||xi - cyj|| - 1) + alpha
  //caffe_axpy(mat_.count(), margin_, Ia_.cpu_data(), pa.mutable_cpu_data());

  //Dtype loss = Dtype(0);
  //for (int i = 0; i < M_; i++) {
    //for (int j = 0; j < M_; j++) {
      //// lij * (||xi - cyj|| - 1) + a <= 0
      //if (pa.cpu_data()[i * M_ + j] <= 0) {
        //mat_data[i * M_ + j] = Dtype(0);
      //}
      //else {
        //mat_data[i * M_ + j] = Dtype(1);
        //loss += pa.cpu_data()[i * M_ + j];
      //}
    //}
  //}
  //loss /= (M_ * Dtype(2));
  //top[0]->mutable_cpu_data()[0] = loss;
//}

//template <typename Dtype>
//void CenterLossLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
    //const vector<bool>& propagate_down,
    //const vector<Blob<Dtype>*>& bottom) {
  //// Gradient with respect to centers
  //if (this->param_propagate_down_[0]) {
    //const Dtype* label = bottom[1]->cpu_data();
    //Dtype* center_diff = this->blobs_[0]->mutable_cpu_diff();
    //Dtype* variation_sum_data = variation_sum_.mutable_cpu_data();
    //const Dtype* distance_data = distance_.cpu_data();

    //// \sum_{y_i==j}
    //caffe_set(N_ * K_, (Dtype)0., variation_sum_.mutable_cpu_data());
    //for (int n = 0; n < N_; n++) {
      //int count = 0;
      //for (int m = 0; m < M_; m++) {
        //const int label_value = static_cast<int>(label[m]);
        //if (label_value == n) {
          //count++;
          //caffe_sub(K_, variation_sum_data + n * K_, distance_data + m * K_, variation_sum_data + n * K_);
        //}
      //}
      //caffe_axpy(K_, (Dtype)1./(count + (Dtype)1.), variation_sum_data + n * K_, center_diff + n * K_);
    //}
  //}
  //// Gradient with respect to bottom data
  //if (propagate_down[0]) {
    //// caffe_copy(M_ * K_, distance_.cpu_data(), bottom[0]->mutable_cpu_diff());
    //Blob<Dtype> scale;
    //scale.ReshapeLike(mat_);
    //// scale: lij / ||xi - cyj||
    //caffe_div(mat_.count(), lij_.cpu_data(), distance_norm_mat_.cpu_data(), scale.mutable_cpu_data());
    //// caffe_copy(mat_.count(), lij_.cpu_data(), scale.mutable_cpu_data());
    //// Iij * lij / ||xi - cyj||
    //caffe_mul(mat_.count(), mat_.cpu_data(), scale.cpu_data(), scale.mutable_cpu_data());
    //Blob<Dtype> matI;
    //matI.ReshapeLike(distance_mat_);
    //// [mat_ * scale, mat_ * scale, ..., mat_ * scale]
    //caffe_cpu_gemm<Dtype>(CblasNoTrans, CblasNoTrans, M_ * M_, K_, 1, 1, scale.cpu_data(), Im_.cpu_data(), 0., matI.mutable_cpu_data());
    //// (xi - cyj) .* [mat_ * scale, mat_ * scale, ..., mat_ * scale]
    //caffe_mul(distance_mat_.count(), distance_mat_.cpu_data(), matI.cpu_data(), matI.mutable_cpu_data());
    //caffe_cpu_gemm<Dtype>(CblasNoTrans, CblasNoTrans, M_, K_, M_ * M_, 1, Ib_.cpu_data(), matI.cpu_data(), 0., bottom[0]->mutable_cpu_diff());
    //caffe_scal(M_ * K_, top[0]->cpu_diff()[0] / (2 * M_), bottom[0]->mutable_cpu_diff());
  //}
  //if (propagate_down[1]) {
    //LOG(FATAL) << this->type()
               //<< " Layer cannot backpropagate to label inputs.";
  //}
//}

//#ifdef CPU_ONLY
//STUB_GPU(CenterLossLayer);
//#endif

//INSTANTIATE_CLASS(CenterLossLayer);
//REGISTER_LAYER_CLASS(CenterLoss);

//}  // namespace caffe

#include <vector>

#include "caffe/filler.hpp"
#include "caffe/layers/center_loss_layer.hpp"
#include "caffe/util/math_functions.hpp"

namespace caffe {

template <typename Dtype>
void CenterLossLayer<Dtype>::LayerSetUp(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top) {
  const int num_output = this->layer_param_.center_loss_param().num_output();
  // alpha
  margin_ = this->layer_param_.center_loss_param().margin();
  N_ = num_output;
  const int axis = bottom[0]->CanonicalAxisIndex(
      this->layer_param_.center_loss_param().axis());
  // Dimensions starting from "axis" are "flattened" into a single
  // length K_ vector. For example, if bottom[0]'s shape is (N, C, H, W),
  // and axis == 1, N inner products with dimension CHW are performed.
  K_ = bottom[0]->count(axis);
  // Check if we need to set up the weights
  if (this->blobs_.size() > 0) {
    LOG(INFO) << "Skipping parameter initialization";
  } else {
    this->blobs_.resize(1);
    // Intialize the weight
    vector<int> center_shape(2);
    center_shape[0] = N_;
    center_shape[1] = K_;
    this->blobs_[0].reset(new Blob<Dtype>(center_shape));
    // fill the weights
    shared_ptr<Filler<Dtype> > center_filler(GetFiller<Dtype>(
        this->layer_param_.center_loss_param().center_filler()));
    center_filler->Fill(this->blobs_[0].get());

  }  // parameter initialization
  this->param_propagate_down_.resize(this->blobs_.size(), true);
}

template <typename Dtype>
void CenterLossLayer<Dtype>::Reshape(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top) {
  CHECK_EQ(bottom[1]->channels(), 1);
  CHECK_EQ(bottom[1]->height(), 1);
  CHECK_EQ(bottom[1]->width(), 1);
  M_ = bottom[0]->num();
  // The top shape will be the bottom shape with the flattened axes dropped,
  // and replaced by a single axis with dimension num_output (N_).
  LossLayer<Dtype>::Reshape(bottom, top);
  distance_.ReshapeLike(*bottom[0]);
  variation_sum_.ReshapeLike(*this->blobs_[0]);

  vector<int> mat_shape(1);
  mat_shape[0] = M_ * N_;
  mat_.Reshape(mat_shape);
  distance_norm_mat_.ReshapeLike(mat_);
  lij_.ReshapeLike(mat_);

  vector<int> distance_mat_shape(2);
  distance_mat_shape[0] = M_ * N_;
  distance_mat_shape[1] = K_;
  distance_mat_.Reshape(distance_mat_shape);

  Ia_.ReshapeLike(mat_);
  Dtype* Ia_data = Ia_.mutable_cpu_data();
  caffe_set(Ia_.count(), Dtype(1), Ia_data);

  vector<int> Ib_shape(2);
  Ib_shape[0] = M_;
  Ib_shape[1] = M_ * N_;
  Ib_.Reshape(Ib_shape);
  Dtype* Ib_data = Ib_.mutable_cpu_data();
  caffe_set(Ib_.count(), Dtype(0), Ib_data);
  for (int i = 0; i < M_; i++) {
    for (int j = i * N_; j < (i + 1) * N_; j++) {
      Ib_data[i * (M_ * N_) + j] = Dtype(1);
    }
  }

  vector<int> Im_shape(1);
  Im_shape[0] = K_;
  Im_.Reshape(Im_shape);
  Dtype* Im_data = Im_.mutable_cpu_data();
  caffe_set(Im_.count(), Dtype(1), Im_data);
}

template <typename Dtype>
void CenterLossLayer<Dtype>::Forward_cpu(const vector<Blob<Dtype>*>& bottom,
    const vector<Blob<Dtype>*>& top) {
  NOT_IMPLEMENTED;
}

template <typename Dtype>
void CenterLossLayer<Dtype>::Backward_cpu(const vector<Blob<Dtype>*>& top,
    const vector<bool>& propagate_down,
    const vector<Blob<Dtype>*>& bottom) {
  NOT_IMPLEMENTED;
}

#ifdef CPU_ONLY
STUB_GPU(CenterLossLayer);
#endif

INSTANTIATE_CLASS(CenterLossLayer);
REGISTER_LAYER_CLASS(CenterLoss);

}  // namespace caffe
