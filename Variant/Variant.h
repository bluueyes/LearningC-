#include <type_traits>
#include <algorithm>
#include <functional>

struct BadVariantAccess : std::exception {
    BadVariantAccess() = default;
    virtual ~BadVariantAccess() = default;

    const char *what() const noexcept override {
        return "BadVariantAccess";
  }
};

template<typename,typename >
struct VariantIndex;

template<typename,size_t>
struct VariantAlterative;

template<typename... Ts>
class Variant{
private:
  size_t m_index;
  alignas(std::max({alignof(Ts)...})) char m_union[std::max({sizeof(Ts)...})];

  //用表存储每个类型的析构函数
  using DestructorFunction = void (*)(char*) noexcept;
  
  static DestructorFunction* destructor_tb() noexcept{
  
    static DestructorFunction func_ptr[sizeof...(Ts)]={
        [](char* union_p) noexcept{
        reinterpret_cast<Ts*>(union_p)->~Ts();
      }...
    };
    return func_ptr;
  }
//const 版本
  template<typename Lambda>
  using ConstVisitorFunction=std::common_type_t<std::invoke_result_t
  <Lambda,Ts&>...>(*)(char const *,Lambda&&);

  template<typename Lambda>
  ConstVisitorFunction<Lambda>* const_visistor_tb() noexcept{
    static ConstVisitorFunction<Lambda> func_ptr[sizeof...(Ts)]={
      [](char const * union_prt,Lambda&& lambda)->std::common_type_t<
          std::invoke_result_t<Lambda, Ts&>...>{
          return std::invoke(std::forward<Lambda>(lambda),*reinterpret_cast<Ts *>(union_prt));
      }...
    }; 
    return func_ptr;
  }

//非const版本
  template<typename Lambda>
  using VisitorFunction=std::common_type_t<std::invoke_result_t
  <Lambda,Ts&>...>(*)(char*,Lambda&&);

  template<typename Lambda>
  VisitorFunction<Lambda>* visistor_tb() noexcept{
    static VisitorFunction<Lambda> func_ptr[sizeof...(Ts)]={
      [](char* union_prt,Lambda&& lambda)->std::common_type_t<
          std::invoke_result_t<Lambda, Ts&>...>{
          return std::invoke(std::forward<Lambda>(lambda),*reinterpret_cast<Ts *>(union_prt));
      }...
    }; 
    return func_ptr;
  }


public:

  template<typename T,typename std::enable_if_t
  <std::disjunction_v<std::is_same<T,Ts>...>,int> = 0>
  Variant(T value):m_index(VariantIndex<Variant,T>::value){
    T* p=reinterpret_cast<T*>(m_union);
    new(p) T(value);
  }


  //禁用赋值和拷贝构造
  Variant(const Variant& )=delete;
  Variant& operator=(const Variant& )=delete;

  ~Variant() noexcept{
    destructor_tb()[m_index](m_union);
  }

  template<typename Lambda>
  std::common_type_t<std::invoke_result_t<Lambda ,Ts &>...>
  visit(Lambda&& lambda){
    return visistor_tb<Lambda>()[index()](m_union,std::forward<Lambda>(lambda));
  }

  template<typename Lambda>
  std::common_type_t<std::invoke_result_t<Lambda ,Ts &>...>
  visit(Lambda&& lambda) const{
    return const_visistor_tb<Lambda>()[index()](m_union,std::forward<Lambda>(lambda));
  }


  size_t index() const{
    return m_index;
  }

  template<typename T>
  constexpr bool holds_alternative()const noexcept{
    return VariantIndex<Variant,T>::value == m_index;
  }

  template<size_t T>
  typename VariantAlterative<Variant,T>::type& get(){
    static_assert(T < sizeof...(Ts),"out of range");
    if(m_index!=T){
      throw BadVariantAccess();
    }
    return *reinterpret_cast<typename VariantAlterative<Variant, T>::type *>(m_union);
  }

  template<typename T>
  T const& get() const{
    return get<VariantIndex<Variant,T>::value>();
  }


  template<size_t T>
  typename VariantAlterative<Variant,T>::type const& get()const { 
    static_assert(T < sizeof...(Ts),"out of range");
    if(m_index!=T){
      throw BadVariantAccess();
    }
    return *reinterpret_cast<typename VariantAlterative<Variant,T>::type *>(m_union);
  }

  template<typename T>
  T& get(){
    return get<VariantIndex<Variant,T>::value>();
  }
};




template<typename T,typename... Ts>
struct VariantIndex<Variant<T,Ts...>,T>{

  static constexpr size_t value=0;
};

template<typename T0,typename T,typename...Ts>
struct VariantIndex<Variant<T0,Ts...>,T>{
  static constexpr size_t value=VariantIndex<Variant<Ts...>,T>::value+1; 
};

template<typename T,typename... Ts>
struct VariantAlterative<Variant<T,Ts...>,0>{
  using type = T;
};


template<typename T,typename... Ts,size_t N>
struct VariantAlterative<Variant<T,Ts...>,N>{
  using type=typename VariantAlterative<Variant<Ts...>,N-1>::type;
};


