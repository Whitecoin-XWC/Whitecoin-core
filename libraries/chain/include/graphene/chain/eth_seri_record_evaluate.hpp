#pragma once
#include <graphene/chain/eth_seri_record.hpp>
#include <graphene/chain/evaluator.hpp>
namespace graphene {
	namespace chain {

		class eth_series_multi_sol_create_evaluator : public evaluator<eth_series_multi_sol_create_evaluator>
		{
		public:
			typedef eth_series_multi_sol_create_operation operation_type;

			void_result do_evaluate(const eth_series_multi_sol_create_operation& o);
			object_id_type do_apply(const eth_series_multi_sol_create_operation& o);
			void pay_fee() override;
			bool if_evluate() { return true; }
		};
		class eth_series_multi_sol_wallfacer_sign_evaluator : public evaluator<eth_series_multi_sol_wallfacer_sign_evaluator>
		{
		public:
			typedef eths_multi_sol_wallfacer_sign_operation operation_type;

			void_result do_evaluate(const eths_multi_sol_wallfacer_sign_operation& o);
			object_id_type do_apply(const eths_multi_sol_wallfacer_sign_operation& o);
			void pay_fee() override;
		};
		class eth_multi_account_create_record_evaluator :public evaluator<eth_multi_account_create_record_evaluator> {
		public:
			typedef eth_multi_account_create_record_operation operation_type;

			void_result do_evaluate(const eth_multi_account_create_record_operation& o);
			object_id_type do_apply(const eth_multi_account_create_record_operation& o);
			void pay_fee() override;
		};
		class eths_wallfacer_sign_final_evaluator : public evaluator<eths_wallfacer_sign_final_evaluator> {
		public:
			typedef eths_wallfacer_sign_final_operation operation_type;
			void_result do_evaluate(const eths_wallfacer_sign_final_operation& o);
			object_id_type do_apply(const eths_wallfacer_sign_final_operation& o);
			void pay_fee() override;
		};
		class eths_coldhot_wallfacer_sign_final_evaluator : public evaluator<eths_coldhot_wallfacer_sign_final_evaluator> {
		public:
			typedef eths_coldhot_wallfacer_sign_final_operation operation_type;
			void_result do_evaluate(const eths_coldhot_wallfacer_sign_final_operation& o);
			object_id_type do_apply(const eths_coldhot_wallfacer_sign_final_operation& o);
			void pay_fee() override;
		};
		class eths_wallfacer_change_signer_evaluator : public evaluator<eths_wallfacer_change_signer_evaluator> {
		public:
			typedef eths_wallfacer_change_signer_operation operation_type;
			void_result do_evaluate(const eths_wallfacer_change_signer_operation& o);
			object_id_type do_apply(const eths_wallfacer_change_signer_operation& o);
			void pay_fee() override;
		};
		class eths_wallfacer_coldhot_change_signer_evaluator : public evaluator<eths_wallfacer_coldhot_change_signer_evaluator> {
		public:
			typedef eths_wallfacer_coldhot_change_signer_operation operation_type;
			void_result do_evaluate(const eths_wallfacer_coldhot_change_signer_operation& o);
			object_id_type do_apply(const eths_wallfacer_coldhot_change_signer_operation& o);
			void pay_fee() override;
		};
		class wallfacer_change_acquire_trx_evaluator : public evaluator<wallfacer_change_acquire_trx_evaluator> {
		public:
			typedef wallfacer_change_acquire_trx_operation operation_type;
			void_result do_evaluate(const wallfacer_change_acquire_trx_operation& o);
			object_id_type do_apply(const wallfacer_change_acquire_trx_operation& o);
			void pay_fee() override;
		};
	}
}
